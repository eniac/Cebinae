

#include <iostream>
#include "bfn_pd_rpc_server.h"
#include <thrift/processor/TMultiplexedProcessor.h>

using namespace ::apache::thrift;

using ::std::shared_ptr;

#include "p4_pd_rpc_server.ipp"

// processor needs to be of type TMultiplexedProcessor,
// I am keeping a void * pointer for 
// now, in case this function is called from C code
int add_to_rpc_server(void *processor) {
  std::cerr << "Adding Thrift service for P4 program main to server\n";

  shared_ptr<mainHandler> main_handler(new mainHandler());

  TMultiplexedProcessor *processor_ = (TMultiplexedProcessor *) processor;
  processor_->registerProcessor(
    "main",
    shared_ptr<TProcessor>(new mainProcessor(main_handler))
  );

  return 0;
}
int rmv_from_rpc_server(void *processor) {
  std::cerr << "Removing Thrift service for P4 program main from server\n";

  TMultiplexedProcessor *processor_ = (TMultiplexedProcessor *) processor;
  processor_->registerProcessor(
    "main",
    shared_ptr<TProcessor>()
  );

  return 0;
}
