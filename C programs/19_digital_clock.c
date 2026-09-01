/*
 * ============================================================
 * PROGRAM: Digital Clock (24-hour format)
 * ============================================================
 * TOPIC: Structures, Time Functions, Loops, System Calls
 * LEVEL: Beginner → Intermediate
 * ============================================================
 *
 * REAL-WORLD SCENARIO:
 * -------------------
 * Timekeeping is fundamental in computing:
 *   - Operating system schedulers use time quanta
 *   - Network protocols use timestamps (NTP, HTTP headers)
 *   - Databases use timestamps for transaction ordering
 *   - Embedded systems: Real-time clocks in microcontrollers
 *   - Gaming: Frame timing, countdown timers, stopwatches
 *
 * WORD PROBLEM:
 * ------------
 * "A train departs at 14:30 and arrives at 18:45. Write a program
 *  to calculate the journey duration. Also create a digital clock
 *  that displays the current time and counts up."
 *
 * TIME REPRESENTATION:
 * ---------------------
 *   In C, time can be represented using:
 *   1. struct tm: Broken-down time (year, month, day, hour, min, sec)
 *   2. time_t: Calendar time (seconds since epoch: Jan 1, 1970)
 *   3. clock_t: Processor time
 *
 * KEY FUNCTIONS:
 * ---------------
 *   time(): Get current calendar time
 *   localtime(): Convert to local time structure
 *   strftime(): Format time as string
 *   clock(): Get processor time
 *   sleep(): Pause execution (POSIX)
 *
 * TIPS & TRICKS:
 * -------------
 *   1. Unix epoch = January 1, 1970, 00:00:00 UTC
 *   2. time_t is typically a long integer representing seconds
 *   3. Use <time.h> for time functions, <unistd.h> for sleep()
 *   4. On Windows, use Sleep() from <windows.h> instead of sleep()
 *   5. 24-hour format: 00:00:00 to 23:59:59
 *   6. 12-hour format: 1:00:00 AM to 12:59:59 PM
 *   7. Leap years: divisible by 4, except centuries not divisible by 400
 *   8. Use system("cls") or system("clear") for console clearing
 *
 * LOGIC FLOW:
 * ----------
 *   1. Start
 *   2. Get current time using time() and localtime()
 *   3. Display formatted time (HH:MM:SS)
 *   4. Loop with sleep(1) to update every second
 *   5. Clear console and redraw each second
 *   6. End
 *
 * COMPLEXITY:
 * ----------
 *   Time Complexity:  O(1) per tick, runs indefinitely
 *   Space Complexity: O(1)
 * ============================================================
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

/*
 * Get current time as a formatted string
 * @param buffer: output buffer to store formatted time
 * @param format: strftime format string
 */
void getCurrentTime(char *buffer, size_t size, const char *format) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buffer, size, format, tm_info);
}

/*
 * Display a stylish digital clock for a given number of seconds
 * @param seconds: duration to display the clock
 */
void displayClock(int seconds) {
    time_t start = time(NULL);
    time_t now;
    char timeStr[20];
    char dateStr[50];

    printf("\n--- Digital Clock (Running for %d seconds) ---\n", seconds);
    printf("Press Ctrl+C to stop early.\n\n");

    while ((int)(time(NULL) - start) < seconds) {
        now = time(NULL);
        struct tm *tm_info = localtime(&now);

        // Format time
        strftime(timeStr, sizeof(timeStr), "%H:%M:%S", tm_info);
        strftime(dateStr, sizeof(dateStr), "%A, %B %d, %Y", tm_info);

        // Clear line and display
        printf("\r⏰ %s    📅 %s", timeStr, dateStr);
        fflush(stdout);  // Force immediate display

        // Alternative: use system("sleep 1") or sleep(1) on POSIX
        struct timespec ts = {1, 0};  // 1 second
        nanosleep(&ts, NULL);
    }
    printf("\n");
}

/*
 * Calculate time difference between two timestamps
 * @param start: start time in seconds since epoch
 * @param end: end time in seconds since epoch
 * @param hours, mins, secs: output durations
 */
void calculateDuration(time_t start, time_t end, int *hours, int *mins, int *secs) {
    long diff = difftime(end, start);
    *hours = diff / 3600;
    *mins = (diff % 3600) / 60;
    *secs = diff % 60;
}

int main() {
    int choice;

    printf("============================================\n");
    printf("        DIGITAL CLOCK PROGRAM\n");
    printf("============================================\n\n");

    while (1) {
        printf("\n--- Clock Menu ---\n");
        printf("  1. Show current time\n");
        printf("  2. Show date and time\n");
        printf("  3. Run stopwatch (10 seconds)\n");
        printf("  4. Calculate time duration\n");
        printf("  0. Exit\n");
        printf("  Enter choice: ");
        scanf("%d", &choice);

        char timeStr[20], dateStr[50];
        time_t start, end;
        int hours, mins, secs;

        switch (choice) {
            case 1:
                getCurrentTime(timeStr, sizeof(timeStr), "%H:%M:%S");
                getCurrentTime(dateStr, sizeof(dateStr), "%A, %B %d, %Y");
                printf("\n⏰ Current Time: %s\n", timeStr);
                printf("📅 Current Date: %s\n", dateStr);
                break;

            case 2:
                getCurrentTime(timeStr, sizeof(timeStr), "%I:%M:%S %p");
                getCurrentTime(dateStr, sizeof(dateStr), "%A, %B %d, %Y");
                printf("\n🕐 Time (12-hour): %s\n", timeStr);
                printf("📅 Date: %s\n", dateStr);
                break;

            case 3:
                printf("\nStopwatch starting... (10 seconds)\n");
                start = time(NULL);
                displayClock(10);
                end = time(NULL);
                calculateDuration(start, end, &hours, &mins, &secs);
                printf("Stopwatch completed! Duration: %02d:%02d:%02d\n",
                       hours, mins, secs);
                break;

            case 4:
                printf("Enter start hour (0-23): ");
                int sh, sm, ss;
                scanf("%d %d %d", &sh, &sm, &ss);
                printf("Enter end hour (0-23): ");
                int eh, em, es;
                scanf("%d %d %d", &eh, &em, &es);

                // Simple calculation (assumes same day)
                start = sh * 3600 + sm * 60 + ss;
                end = eh * 3600 + em * 60 + es;
                if (end < start) end += 24 * 3600;  // Crosses midnight
                calculateDuration(start, end, &hours, &mins, &secs);
                printf("\nDuration: %02d hours, %02d minutes, %02d seconds\n",
                       hours, mins, secs);
                break;

            case 0:
                printf("Goodbye! 👋\n");
                return 0;

            default:
                printf("[ERROR] Invalid choice!\n");
        }
    }

    return 0;
}
/*
 * COMPILATION:
 *   gcc 19_digital_clock.c -o digital_clock
 *
 * SAMPLE OUTPUT:
 *   Current Time: 14:35:22
 *   Date: Monday, September 01, 2026
 *
 * TRICK: Use fflush(stdout) after printf when you need
 *        immediate output without a newline (like a real-time clock).
 *        \r (carriage return) moves cursor to beginning of line.
 */