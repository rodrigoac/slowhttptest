/*****************************************************************************
 * Licensed to Qualys, Inc. (QUALYS) under one or more
 * contributor license agreements. See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * QUALYS licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * *****************************************************************************/

/*****
 * Author: Sergey Shekyan sshekyan@qualys.com
 *
 * Slow HTTP attack  vulnerability test tool
 *  http://code.google.com/p/slowhttptest/
 *
 *  class SlowHTTPTest implements main functionality of slow HTTP attack
 *  vulnerability detection. before calling run_test(), class has to be initialized.
 *****/

#ifndef _SLOWHTTPTEST_H_
#define _SLOWHTTPTEST_H_

#include "netdb.h"
#include <string>
#include <vector>

#include "slowurl.h"

namespace slowhttptest {

enum SlowTestType {
  eHeader = 0,
  ePost
};

class SlowSocket;
class SlowHTTPTest {
 public:
  SlowHTTPTest(int delay, int duration, int interval, int con_cnt, SlowTestType type);
  ~SlowHTTPTest();

  bool init(const char* url);
  void report_parameters();
  bool run_test();
  static bool fillRandomData(char * random_string, const size_t len);
  static bool grabResponseCode(const char *buf, int& code);

 private:
  void remove_sock(int id);

  hostent* server_;
  std::string request_;
  std::string random_post_;
  std::string user_agent_;
  Url base_uri_;

  std::vector<SlowSocket*> sock_;
  int delay_;
  int duration_;
  int followup_timing_;
  int followup_cnt_;
  int num_connections_;

  SlowTestType type_;
};

}  // namespace slowhttptest
#endif
