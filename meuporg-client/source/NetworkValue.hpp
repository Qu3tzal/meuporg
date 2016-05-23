#ifndef NETWORKVALUE_HPP_INCLUDED
#define NETWORKVALUE_HPP_INCLUDED

#include <SFML/System.hpp>

namespace NetworkValue
{
    const unsigned int VERSION(000);
   	const unsigned int	NUMBER_OF_PLAYERS(001);
	const unsigned int	MAP_NAME(002);

	const unsigned int	CONNECT(100);
	const unsigned int	ACCOUNT_CREATED_RECONNECT(101);
	const unsigned int	CONNECTION_SUCCESS(102);
	const unsigned int	CONNECION_FAIL(103);
	const unsigned int	CONNECTION_FAIL_VERSION_ERROR(104);
	const unsigned int	CONNECTION_FAIL_SERVER_FULL(105);
	const unsigned int	CONNECTION_FAIL_UNKNOWN_ERROR(106);
} // namespace NetworkValue.

#endif // NETWORKVALUE_HPP_INCLUDED
