#ifndef NETWORKVALUES_HPP_INCLUDED
#define NETWORKVALUES_HPP_INCLUDED

namespace NetworkValues
{
    const unsigned int  VERSION(000);
   	const unsigned int	NUMBER_OF_PLAYERS(001);

	const unsigned int	CONNECT(100);
	const unsigned int	ACCOUNT_CREATED_RECONNECT(101);
	const unsigned int	CONNECTION_SUCCESS(102);
	const unsigned int	CONNECION_FAIL(103);
	const unsigned int	CONNECTION_FAIL_VERSION_ERROR(104);
	const unsigned int	CONNECTION_FAIL_SERVER_FULL(105);
	const unsigned int	CONNECTION_FAIL_UNKNOWN_ERROR(106);
	const unsigned int  CONNECTION_FAIL_UNKNOWN_USER(107);
	const unsigned int  CONNECTION_FAIL_ALREADY_CONNECTED(108);
	const unsigned int  CONNECTION_FAIL_WRONG_TOKEN(109);

	const unsigned int  NOTIFY(200);
	const unsigned int  DISCONNECT(201);
	const unsigned int  INPUT(202);
	const unsigned int  ENTITY_REMOVED(203);
	const unsigned int  PLAYER_CONNECTED(204);
	const unsigned int  PLAYER_DISCONNECTED(205);
	const unsigned int  RECEIVE_CHAT_MESSAGE(206);
	const unsigned int  SEND_CHAT_MESSAGE(207);
	const unsigned int  UPDATE(208);
	const unsigned int  MISSION_START(209);
    const unsigned int  MISSION_END(210);
    const unsigned int  MISSION_PROGRESS(211);
    const unsigned int  KILL(212);
    const unsigned int  LEVEL_UP(213);
    const unsigned int  ACCEPT_MISSION(214);
    const unsigned int  CANCEL_MISSION(215);
    const unsigned int  PLAYER_MOVED_TO_WORLD(216);
    const unsigned int  RESPAWN(217);

	const unsigned int  KEEP_ALIVE(300);
	const unsigned int  OKAY(301);
} // namespace NetworkValues.

#endif // NETWORKVALUES_HPP_INCLUDED
