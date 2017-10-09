#include <eoslib/eos.hpp>

extern "C" {
    void init()  {
       eos::print( "Init World!\n" );
    }

	struct transfer {
	   uint64_t from;	//account name | a-z , 12 chars or 13 ('.' a-p)
	   uint64_t to;		//account name
	   uint64_t amount;	//value
	};

	void apply( uint64_t code, uint64_t action ) {
	   eos::print( "Hello World: ", eos::Name(code)/*name of account with code*/, "->", eos::Name(action), "\n" );
	   /* Name () wraps a uint64_t to ensure it is only passed to methods that expect a Name and that no mathematical operations occur.
	   *  It also enables specialization of print so that it is printed as a base32 string.
	   */
	   if( action == N(transfer) ) {
	      auto message = eos::currentMessage<transfer>();
	      /* The auto keyword directs the compiler to use the initialization expression of a declared variable, 
	      *  or lambda expression parameter, to deduce its type.
	      */
	      assert( message.amount > 0, "Must transfer an amount greater than 0" );
	      /* void assert 	( 	uint32_t  	test, const char * cstr	) 	
	      *  Aborts processing of this message and unwinds all pending changes if the test condition is true 
	      *  Parameters: test (- 0 to abort, 1 to ignore), cstr	(- a null terminated message to explain the reason for failure) 
	      */
	      eos::requireAuth( message.from );
	      /* void requireAuth 	( 	AccountName  	name	) 	
	      *	 Verifies that name exists in the set of provided auths on a message. Throws if not found
	      *	 Parameters: name (- name of the account to be verified )	
	      */
	      eos::print( "Transfer ", message.amount, " from ", message.from, " to ", message.to, "\n" );
	   }
	}
}
/* INPUT
* ./eosc push message tester transfer '{"from": "currency", "to": "inita", "amount" : 1000}' -S tester -p currency@active
*  OUTPUT
* Init World!
* Hello World: tester->transfer
* Transfer 1000 from 5093418677655568384 to 8421048506461978624*/