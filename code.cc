 Cycles lastRunningCycle;




template<class Impl>
 bool
 LSQ<Impl>::cacheBlocked() const
 {
     return _cacheBlocked;
 }
  
 template<class Impl>
 void
 LSQ<Impl>::cacheBlocked(bool v)
 {
     _cacheBlocked = v;
 }

