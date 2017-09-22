#include <task/task.hpp>
#include <eoslib/print.hpp>

namespace task {
   using namespace eos;

   void sendMsg( const task::Message& msg ) {
      print("Hello, World: ");
      print("\n");
   }
}

using namespace task;

extern "C" {
    void init()  {}

    void apply(uint64_t code, uint64_t action) {
       if (code == N(task)) {
          if (action == N(message)) 
             task::sendMsg(currentMessage< task::Message >());
      }
    }
}
