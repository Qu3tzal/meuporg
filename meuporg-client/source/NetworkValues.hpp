#ifndef NETWORKVALUES_HPP_INCLUDED
#define NETWORKVALUES_HPP_INCLUDED

#include <SFML/System.hpp>

namespace NetworkValues
{
    const sf::Uint64  VERSION(000);
   	const sf::Uint64	NUMBER_OF_PLAYERS(001);
   	const sf::Uint64	PING(002);

	const sf::Uint64	CONNECT(100);
	const sf::Uint64	ACCOUNT_CREATED_RECONNECT(101);
	const sf::Uint64	CONNECTION_SUCCESS(102);
	const sf::Uint64	CONNECION_FAIL(103);
	const sf::Uint64	CONNECTION_FAIL_VERSION_ERROR(104);
	const sf::Uint64	CONNECTION_FAIL_SERVER_FULL(105);
	const sf::Uint64	CONNECTION_FAIL_UNKNOWN_ERROR(106);
	const sf::Uint64	CONNECTION_FAIL_UNKNOWN_USER(107);
	const sf::Uint64	CONNECTION_FAIL_ALREADY_CONNECTED(108);
	const sf::Uint64  CONNECTION_FAIL_WRONG_TOKEN(109);

    const sf::Uint64  NOTIFY(200);
    const sf::Uint64  DISCONNECT(201);
	const sf::Uint64	INPUT(202);
	const sf::Uint64	ENTITY_REMOVED(203);
	const sf::Uint64	PLAYER_CONNECTED(204);
	const sf::Uint64	PLAYER_DISCONNECTED(205);
	const sf::Uint64	RECEIVE_CHAT_MESSAGE(206);
	const sf::Uint64	SEND_CHAT_MESSAGE(207);
	const sf::Uint64	UPDATE(208);
	const sf::Uint64  MISSION_START(209);
    const sf::Uint64  MISSION_END(210);
    const sf::Uint64  MISSION_PROGRESS(211);
    const sf::Uint64  KILL(212);
    const sf::Uint64  LEVEL_UP(213);
    const sf::Uint64  ACCEPT_MISSION(214);
	const sf::Uint64	CANCEL_MISSION(215);
    const sf::Uint64	PLAYER_MOVED_TO_WORLD(216);
    const sf::Uint64	RESPAWN(217);

	const sf::Uint64	KEEP_ALIVE(300);
	const sf::Uint64	OKAY(301);
} // namespace NetworkValues.

#endif // NETWORKVALUES_HPP_INCLUDED
