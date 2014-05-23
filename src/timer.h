#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>
#include <set>

using std::chrono::milliseconds;

struct Timer {
   Timer(milliseconds expiration_time, bool start_active=false);
   Timer(const Timer&)=delete;
   Timer& operator=(const Timer&)=delete;
   ~Timer();

   void reset();

   bool is_active() const;
   bool is_expired() const;

   milliseconds current_time() const;

   static void updateAll(milliseconds elapsed_time);
private:
   void update(milliseconds elapsed_time);
   milliseconds current_time_;
   const milliseconds expiration_time_;

   static std::set<Timer*> timers_;
};

#endif /* TIMER_H_ */
