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

    
 
 LSQUnit<Impl>::trySendPacket(bool isLoad, PacketPtr data_pkt)
 1219 {​​​​​​​​
 1220  bool ret = true;
 1221  bool cache_got_blocked = false;
 1222 
 1223  auto state = dynamic_cast<LSQSenderState*>(data_pkt->senderState);
 1224 
 1225  if (!lsq->cacheBlocked() &&
 1226  lsq->cachePortAvailable(isLoad)) {​​​​​​​​
 1227  if (!dcachePort->sendTimingReq(data_pkt)) {​​​​​​​​
 1228  ret = false;
 1229  cache_got_blocked = true;
 1230  }​​​​​​​​
 1231  }​​​​​​​​ else {​​​​​​​​
 1232  ret = false;
 1233  }​​​​​​​​
 1234 
 1235  if (ret) {​​​​​​​​
 1236  if (!isLoad) {​​​​​​​​
 1237  isStoreBlocked = false;
 1238  }​​​​​​​​
 1239  lsq->cachePortBusy(isLoad);
 1240  state->outstanding++;
 1241  state->request()->packetSent();
 1242  }​​​​​​​​ else {​​​​​​​​
 1243  if (cache_got_blocked) {​​​​​​​​
 1244  lsq->cacheBlocked(true);
 1245  ++stats.blockedByCache;
 1246  }​​​​​​​​
 1247  if (!isLoad) {​​​​​​​​
 1248  assert(state->request() == storeWBIt->request());
 1249  isStoreBlocked = true;
 1250  }​​​​​​​​
 1251  state->request()->packetNotSent();
 1252  }​​​​​​​​
 1253  return ret;
 1254 }​​​​​​​​


