/*
 * C/C++ header file for calling server start function from C code
 */

#ifndef _BFN_PD_RPC_SERVER_H_
#define _BFN_PD_RPC_SERVER_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int add_to_rpc_server(void *processor);
extern int rmv_from_rpc_server(void *processor);

#ifdef __cplusplus
}
#endif



#endif /* _BFN_PD_RPC_SERVER_H_ */
