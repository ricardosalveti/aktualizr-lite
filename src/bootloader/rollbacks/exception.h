#ifndef AKTUALIZR_LITE_EXCEPTION_ROLLBACK_H_
#define AKTUALIZR_LITE_EXCEPTION_ROLLBACK_H_

#include "rollback.h"
#include "utilities/exceptions.h"

class ExceptionRollback : public Rollback {
 public:
  ExceptionRollback() : Rollback() {}
  void setBootOK() { throw NotImplementedException(); }
  void updateNotify() { throw NotImplementedException(); }
  void installNotify(const Uptane::Target& target) { throw NotImplementedException(); }
};

#endif  // AKTUALIZR_LITE_EXCEPTION_ROLLBACK_H_
