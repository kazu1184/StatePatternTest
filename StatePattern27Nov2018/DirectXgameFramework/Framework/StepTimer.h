//
// StepTimer.h - A simple timer that provides elapsed time information
//

#pragma once

#include <exception>
#include <stdint.h>

namespace DX
{
    // アニメーションやシミュレーションタイミングのためのヘルパークラス(Helper class for animation and simulation timing)
    class StepTimer {
    public:
        StepTimer() : 
            m_elapsedTicks(0),
            m_totalTicks(0),
            m_leftOverTicks(0),
            m_frameCount(0),
            m_framesPerSecond(0),
            m_framesThisSecond(0),
            m_qpcSecondCounter(0),
            m_isFixedTimeStep(false),
            m_targetElapsedTicks(TicksPerSecond / 60) {
            if (!QueryPerformanceFrequency(&m_qpcFrequency)) {
                throw std::exception( "QueryPerformanceFrequency" );
            }

            if (!QueryPerformanceCounter(&m_qpcLastTime)) {
                throw std::exception( "QueryPerformanceCounter" );
            }

            // 1秒の1/10への最大デルタを初期化する (Initialize max delta to 1/10 of a second)
            m_qpcMaxDelta = m_qpcFrequency.QuadPart / 10;
        }

        // 直前のUpdate呼び出しからの経過時間を取得する (Get elapsed time since the previous Update call)
        uint64_t GetElapsedTicks() const	{ return m_elapsedTicks; }
        double GetElapsedSeconds() const	{ return TicksToSeconds(m_elapsedTicks); }

        // プログラム開始からの総時間を取得する (Get total time since the start of the program)
        uint64_t GetTotalTicks() const		{ return m_totalTicks; }
        double GetTotalSeconds() const		{ return TicksToSeconds(m_totalTicks); }

        // プログラム開始からのUpdateの総数 (Get total number of updates since start of the program)
        uint32_t GetFrameCount() const		{ return m_frameCount; }

        // 現在のフレームレート (Get the current framerate)
        uint32_t GetFramesPerSecond() const	{ return m_framesPerSecond; }

        // 固定または可変タイムステップモードを使用するかどうかを設定する (Set whether to use fixed or variable timestep mode)
        void SetFixedTimeStep(bool isFixedTimestep)	{ m_isFixedTimeStep = isFixedTimestep; }

        // 固定タイムステップモードの際、Updateの呼び出しの頻度を設定する (Set how often to call Update when in fixed timestep mode)
        void SetTargetElapsedTicks(uint64_t targetElapsed)	{ m_targetElapsedTicks = targetElapsed; }
        void SetTargetElapsedSeconds(double targetElapsed)	{ m_targetElapsedTicks = SecondsToTicks(targetElapsed); }

        // １秒間に10,000,000 tick に使用するときの整数形式表現 (Integer format represents time using 10,000,000 ticks per second)
        static const uint64_t TicksPerSecond = 10000000;

        static double TicksToSeconds(uint64_t ticks)		{ return static_cast<double>(ticks) / TicksPerSecond; }
        static uint64_t SecondsToTicks(double seconds)		{ return static_cast<uint64_t>(seconds * TicksPerSecond); }

        // After an intentional timing discontinuity (for instance a blocking IO operation)
        // call this to avoid having the fixed timestep logic attempt a set of catch-up 
        // Update calls.

        void ResetElapsedTime() {
            if (!QueryPerformanceCounter(&m_qpcLastTime)) {
                throw std::exception("QueryPerformanceCounter");
            }

            m_leftOverTicks = 0;
            m_framesPerSecond = 0;
            m_framesThisSecond = 0;
            m_qpcSecondCounter = 0;
        }

        // Updateタイマーステート 指定されたUpdate関数の呼び出し Update timer state, calling the specified Update function the appropriate number of times.
        template<typename TUpdate>
        void Tick(const TUpdate& update) {
            // 現在の時間を問い合わせる (Query the current time)
            LARGE_INTEGER currentTime;

            if (!QueryPerformanceCounter(&currentTime)) {
                throw std::exception( "QueryPerformanceCounter" );
            }

            uint64_t timeDelta = currentTime.QuadPart - m_qpcLastTime.QuadPart;

            m_qpcLastTime = currentTime;
            m_qpcSecondCounter += timeDelta;

            // 過度のラージタイムデルタを最大範囲に留める (デバッグのポーズの後など) Clamp excessively large time deltas (e.g. (after paused in the debugger)
            if (timeDelta > m_qpcMaxDelta) {
                timeDelta = m_qpcMaxDelta;
            }

            // 標準的なテック形式でQPC単位に変換する.オーバーフローできない (Convert QPC units into a canonical tick format. This cannot overflow due to the previous clamp)
            timeDelta *= TicksPerSecond;
            timeDelta /= m_qpcFrequency.QuadPart;

            uint32_t lastFrameCount = m_frameCount;

            if (m_isFixedTimeStep) {
                // 固定タイムステップ更新ロジック (Fixed timestep update logic)
				// アプリがターゲットの経過時間(1/4ミリ秒)に接近して動作する場合、ターゲット値にマッチするためにクロックをクランプする
				// 
                // If the app is running very close to the target elapsed time (within 1/4 of a millisecond) just clamp
                // the clock to exactly match the target value. This prevents tiny and irrelevant errors
                // from accumulating over time. Without this clamping, a game that requested a 60 fps
                // fixed update, running with vsync enabled on a 59.94 NTSC display, would eventually
                // accumulate enough tiny errors that it would drop a frame. It is better to just round 
                // small deviations down to zero to leave things running smoothly.

                if (abs(static_cast<int64_t>(timeDelta - m_targetElapsedTicks)) < TicksPerSecond / 4000) {
                    timeDelta = m_targetElapsedTicks;
                }

                m_leftOverTicks += timeDelta;

                while (m_leftOverTicks >= m_targetElapsedTicks) {
                    m_elapsedTicks = m_targetElapsedTicks;
                    m_totalTicks += m_targetElapsedTicks;
                    m_leftOverTicks -= m_targetElapsedTicks;
                    m_frameCount++;

                    update();
                }
            }
            else {
                // 可変タイムステップ更新ロジック (Variable timestep update logic)
                m_elapsedTicks = timeDelta;
                m_totalTicks += timeDelta;
                m_leftOverTicks = 0;
                m_frameCount++;

                update();
            }

            // Track the current framerate.
            if (m_frameCount != lastFrameCount) {
                m_framesThisSecond++;
            }

            if (m_qpcSecondCounter >= static_cast<uint64_t>(m_qpcFrequency.QuadPart)) {
                m_framesPerSecond = m_framesThisSecond;
                m_framesThisSecond = 0;
                m_qpcSecondCounter %= m_qpcFrequency.QuadPart;
            }
        }

    private:
        // Source timing data uses QPC units.
        LARGE_INTEGER m_qpcFrequency;
        LARGE_INTEGER m_qpcLastTime;
        uint64_t m_qpcMaxDelta;

        // Derived timing data uses a canonical tick format.
        uint64_t m_elapsedTicks;
        uint64_t m_totalTicks;
        uint64_t m_leftOverTicks;

        // Members for tracking the framerate.
        uint32_t m_frameCount;
        uint32_t m_framesPerSecond;
        uint32_t m_framesThisSecond;
        uint64_t m_qpcSecondCounter;

        // Members for configuring fixed timestep mode.
        bool m_isFixedTimeStep;
        uint64_t m_targetElapsedTicks;
    };
}
