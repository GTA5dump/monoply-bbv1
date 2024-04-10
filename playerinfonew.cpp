
void DrawTextF(float x, float y, int font, int red, int green, int blue, float scale, bool outline, char* text)
{
	HUD::SET_TEXT_FONT(font);
	HUD::SET_TEXT_SCALE(0.0, scale);
	HUD::SET_TEXT_COLOUR(red, green, blue, 255);
	HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	if (outline)
		HUD::SET_TEXT_OUTLINE();
	HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
}
int GetSpeed(Ped ped) {

	int speed = (int)round(ENTITY::GET_ENTITY_SPEED(ped) * 2.24);
	return speed;
}
void playerinfo(int playerid) {
	float baseX = 0.47f;
	float baseY = 0.035f;
	char price[128];
	Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(playerid);
	Vector3 get_coords = ENTITY::GET_ENTITY_COORDS(ped, 0);
	int NETWORK_HANDLE[76];
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(playerid, &NETWORK_HANDLE[0], 13);
	const char* rockstarID = rockstarID = NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&NETWORK_HANDLE[0]);
	std::string Speed = std::to_string(GetSpeed(ped));
	Hash street[2]{};
	PATHFIND::GET_STREET_NAME_AT_COORD(get_coords.x, get_coords.y, get_coords.z, &street[0], &street[1]);
	const char* Street = HUD::GET_STREET_NAME_FROM_HASH_KEY(street[0]);
	const char* Zone = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ZONE::GET_NAME_OF_ZONE(get_coords.x, get_coords.y, get_coords.z));
	sprintf(price, "%s", Street);
	const char* money = monopoly::script_global::script_global(1853910).at(playerid, 862).at(205).at(3).as<const char*>();
	

	


	Vector3 sc = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_ID(), false);
	Vector3 pc = ENTITY::GET_ENTITY_COORDS(ped, false);

	/*GRAPHICS::DRAW_RECT(baseX + 0.08f, baseY + 0.23f, 0.2f, 0.33f, 0, 0, 0, 140, 0);*/
	GRAPHICS::DRAW_SPRITE("Textures", "player_info", baseX + 0.08f, baseY + 0.23f, 0.2f, 0.50f, 0.33f, 255, 255, 255, 255, 0);
	/*GRAPHICS::DRAW_SPRITE("Textures", "player_information_header", baseX + 0.08f, baseY + 0.23f, 0.2f, 0.50f, 0.33f, 255, 255, 255, 255, 0);*/

	GRAPHICS::DRAW_RECT(baseX + 0.08f, baseY - 1.0f, 0.2f, 0.002f, 255, 255, 255, 255, 0);
	DrawTextF(baseX + 0.040f, baseY + 0.06f, 0, 255, 255, 255, 0.31f, false, (char*)"PLAYER INFO");
    DrawTextF(baseX + 0.001f, baseY + 0.10f, 0, 255, 255, 255, 0.24f, false, (char*)"Modder"); //left
	//DrawTextF(baseX + 0.1f, baseY + 0.12f, 0, 255, 255, 255, 0.24f, false, (char*)"0%"); //right
	if (!ENTITY::IS_ENTITY_VISIBLE(ped) && playerid != PLAYER::PLAYER_ID() && !PLAYER::GET_PLAYER_INVINCIBLE(ped) && !SYSTEM::VDIST(sc.x, sc.y, sc.z, pc.x, pc.y, pc.z) < 5.0f) {
		DrawTextF(baseX + 0.1f, baseY + 0.10f, 0, 255, 255, 255, 0.24f, false, (char*)"3%"); //right
	}
	else if (!ENTITY::IS_ENTITY_VISIBLE(ped) && playerid != PLAYER::PLAYER_ID() && !PLAYER::GET_PLAYER_INVINCIBLE(ped) && SYSTEM::VDIST(sc.x, sc.y, sc.z, pc.x, pc.y, pc.z) < 5.0f) {
		DrawTextF(baseX + 0.1f, baseY + 0.10f, 0, 255, 255, 255, 0.24f, false, (char*)"25%"); //right
	}
	else if (PLAYER::GET_PLAYER_INVINCIBLE(ped) && playerid != PLAYER::PLAYER_ID() && ENTITY::IS_ENTITY_VISIBLE(ped)) {
		DrawTextF(baseX + 0.1f, baseY + 0.10f, 0, 255, 255, 255, 0.24f, false, (char*)"20%"); //right
	}
	else if (PLAYER::GET_PLAYER_INVINCIBLE(ped) && playerid != PLAYER::PLAYER_ID() && ENTITY::IS_ENTITY_VISIBLE(ped)) {
		DrawTextF(baseX + 0.1f, baseY + 0.10f, 0, 255, 255, 255, 0.24f, false, (char*)"35%"); //right
	}
	else if (PLAYER::GET_PLAYER_INVINCIBLE(ped) && playerid != PLAYER::PLAYER_ID() && SYSTEM::VDIST(sc.x, sc.y, sc.z, pc.x, pc.y, pc.z) < 5.0f) {
		DrawTextF(baseX + 0.1f, baseY + 0.10f, 0, 255, 255, 255, 0.24f, false, (char*)"50%"); //right
	}
	else if (playerid == PLAYER::PLAYER_ID()) {
		DrawTextF(baseX + 0.1f, baseY + 0.10f, 0, 255, 255, 255, 0.24f, false, (char*)"100%"); //right
	}
	else {
		DrawTextF(baseX + 0.1f, baseY + 0.10f, 0, 255, 255, 255, 0.24f, false, (char*)"Probably not"); //right
	}
	DrawTextF(baseX + 0.001f, baseY + 0.12f, 0, 255, 255, 255, 0.24f, false, (char*)"Alive"); //left
	if (PED::IS_PED_DEAD_OR_DYING(ped, 0))
		DrawTextF(baseX + 0.1f, baseY + 0.12f, 0, 255, 255, 255, 0.24f, false, (char*)"No"); //right
	else
		DrawTextF(baseX + 0.1f, baseY + 0.12f, 0, 255, 255, 255, 0.24f, false, (char*)"Yes"); //right
	DrawTextF(baseX + 0.001f, baseY + 0.14f, 0, 255, 255, 255, 0.24f, false, (char*)"Visible"); //left
	if (!ENTITY::IS_ENTITY_VISIBLE(ped))
	{
		DrawTextF(baseX + 0.1f, baseY + 0.14f, 0, 255, 255, 255, 0.24f, false, (char*)"No"); //right
	}
	else
	{
		DrawTextF(baseX + 0.1f, baseY + 0.14f, 0, 255, 255, 255, 0.24f, false, (char*)"Yes"); //right
	}
	DrawTextF(baseX + 0.001f, baseY + 0.16f, 0, 255, 255, 255, 0.24f, false, (char*)"God Mode"); //left
	if (PLAYER::GET_PLAYER_INVINCIBLE(ped))
	{
		DrawTextF(baseX + 0.1f, baseY + 0.16f, 0, 255, 255, 255, 0.24f, false, (char*)"Yes"); //right
	}
	else
	{
		DrawTextF(baseX + 0.1f, baseY + 0.16f, 0, 255, 255, 255, 0.24f, false, (char*)"No"); //right
	}
	DrawTextF(baseX + 0.001f, baseY + 0.18f, 0, 255, 255, 255, 0.24f, false, (char*)"In Vehicle"); //left
	if (PED::IS_PED_IN_ANY_VEHICLE(ped, 0))
		DrawTextF(baseX + 0.1f, baseY + 0.18f, 0, 255, 255, 255, 0.24f, false, (char*)"Yes"); //right
	else
	DrawTextF(baseX + 0.1f, baseY + 0.18f, 0, 255, 255, 255, 0.24f, false, (char*)"No"); //right
	DrawTextF(baseX + 0.001f, baseY + 0.20f, 0, 255, 255, 255, 0.24f, false, (char*)"money"); //left
	DrawTextF(baseX + 0.1f, baseY + 0.20f, 0, 255, 255, 255, 0.24f, false, (char*)money);
	DrawTextF(baseX + 0.001f, baseY + 0.22f, 0, 255, 255, 255, 0.24f, false, (char*)"Zone"); //left
	DrawTextF(baseX + 0.1f, baseY + 0.22f, 0, 255, 255, 255, 0.24f, false, (char*)Zone); //right
	DrawTextF(baseX + 0.001f, baseY + 0.24f, 0, 255, 255, 255, 0.24f, false, (char*)"Street"); //left
	DrawTextF(baseX + 0.1f, baseY + 0.24f, 0, 255, 255, 255, 0.24f, false, (char*)Street); //right
	DrawTextF(baseX + 0.001f, baseY + 0.26f, 0, 255, 255, 255, 0.24f, false, (char*)"speed"); //left
	DrawTextF(baseX + 0.1f, baseY + 0.26f, 0, 255, 255, 255, 0.24f, false, (char*)std::to_string(ENTITY::GET_ENTITY_SPEED(ped)).c_str()); //right
	DrawTextF(baseX + 0.001f, baseY + 0.28f, 0, 255, 255, 255, 0.24f, false, (char*)"Heading"); //left
	DrawTextF(baseX + 0.1f, baseY + 0.28f, 0, 255, 255, 255, 0.24f, false, (char*)std::to_string(ENTITY::GET_ENTITY_HEADING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(playerid))).c_str()); //right
	//DrawTextF(baseX + 0.001f, baseY + 0.28f, 0, 255, 255, 255, 0.24f, false, (char*)"Model"); //left
	//DrawTextF(baseX + 0.1f, baseY + 0.28f, 0, 255, 255, 255, 0.24f, false, (char*)std::to_string(ENTITY::GET_ENTITY_MODEL(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(playerid))).c_str()); //right
	DrawTextF(baseX + 0.001f, baseY + 0.30f, 0, 255, 255, 255, 0.24f, false, (char*)"Rockstar ID"); //left
	DrawTextF(baseX + 0.1f, baseY + 0.30f, 0, 255, 255, 255, 0.24f, false, (char*)rockstarID); //right
	DrawTextF(baseX + 0.001f, baseY + 0.32f, 0, 255, 255, 255, 0.24f, false, (char*)"IP Address"); //left


	DrawTextF(baseX + 0.001f, baseY + 0.34f, 0, 255, 255, 255, 0.24f, false, (char*)"Wanted Level"); //left
	DrawTextF(baseX + 0.1f, baseY + 0.34f, 0, 255, 255, 255, 0.24f, false, (char*)std::to_string(PLAYER::GET_PLAYER_WANTED_LEVEL(playerid)).c_str()); //right
	DrawTextF(baseX + 0.001f, baseY + 0.36f, 0, 255, 255, 255, 0.24f, false, (char*)"player health"); //left
	DrawTextF(baseX + 0.1f, baseY + 0.36f, 0, 255, 255, 255, 0.24f, false, (char*)std::to_string(ENTITY::GET_ENTITY_HEALTH(ped)).c_str()); //right





}
BOOL IsPlayerFriend(Player player)
{
	int handle[76];
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &handle[0], 13);
	return NETWORK::NETWORK_IS_FRIEND(&handle[0]);
}
auto SelectedPlayer = NULL;


