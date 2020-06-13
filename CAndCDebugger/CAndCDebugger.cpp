// CAndCDebugger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <fstream>
#include <iostream>
#include "../TIBERIANDAWN/DLLInterface.h"
#include <boost\archive\text_oarchive.hpp>
#include <boost/archive/tmpdir.hpp>

#include <boost/archive/text_iarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>

void Callback(const EventCallbackStruct& event)
{
	//so can debug
	int i = 0;
	switch (event.EventType)
	{
		case EventCallbackType::CALLBACK_EVENT_ACHIEVEMENT:
			i++;
			break;
		case EventCallbackType::CALLBACK_EVENT_BRIEFING_SCREEN:
			i++;
			break;
		case EventCallbackType::CALLBACK_EVENT_CENTER_CAMERA:
			i++;
			break;
		case EventCallbackType::CALLBACK_EVENT_DEBUG_PRINT:
			i++;
			break;
		case EventCallbackType::CALLBACK_EVENT_GAME_OVER:
			i++;
			break;
		case EventCallbackType::CALLBACK_EVENT_INVALID:
			i++;
			break;
		case EventCallbackType::CALLBACK_EVENT_MESSAGE:
			i++;
			break;
		case EventCallbackType::CALLBACK_EVENT_MOVIE:
			i++;
			break;
		case EventCallbackType::CALLBACK_EVENT_PING:
			i++;
			break;
		case EventCallbackType::CALLBACK_EVENT_SOUND_EFFECT:
			i++;
			break;
		case EventCallbackType::CALLBACK_EVENT_SPECIAL_WEAPON_TARGETTING:
			i++;
			break;
		case EventCallbackType::CALLBACK_EVENT_SPEECH:
			i++;
			break;
		case EventCallbackType::CALLBACK_EVENT_STORE_CARRYOVER_OBJECTS:
			i++;
			break;
		case EventCallbackType::CALLBACK_EVENT_UPDATE_MAP_CELL:
			i++;
			break;
	}
}

int main()
{	
	std::ifstream ifs("events_in.txt");
    boost::archive::text_iarchive ia(ifs);
	CNCDebug_DisableEventOutput();
    while (true)
    {
		if (ifs.peek() == EOF)
			break;

        std::string event_name;
        std::string event_time;
        ia >> event_name;
        ia >> event_time;

		std::time_t t = std::time_t(std::stoll(event_time));
		struct tm  dateTimeStruct;
		char       dateTimeString[80];
		dateTimeStruct = *localtime(&t);
		strftime(dateTimeString, sizeof(dateTimeString), "%Y-%m-%d.%X", &dateTimeStruct);


		if (event_name == "CNC_Version")
		{
			std::string version_in;
			ia >> version_in;
			CNC_Version(std::stoi(version_in));
			continue;
		}      
		if (event_name == "CNC_Add_Mod_Path")
		{
			std::string modPath;
			ia >> modPath;
			CNC_Add_Mod_Path(modPath.c_str());
			continue;
		}
		if (event_name == "CNC_Init")
		{
			std::string command_line;
			ia >> command_line;
			CNC_Init(command_line.c_str(), Callback);
			continue;
		}
		if (event_name == "CNC_Config")
		{
			CNCRulesDataStruct rules;
			ia >> rules;
			CNC_Config(rules);
			continue;
		}
		if (event_name == "CNC_Start_Instance_Variation")
		{
			std::string scenario_index;
			std::string scenario_variation;
			std::string scenario_direction;
			std::string build_level;
			std::string faction;
			std::string game_type;
			std::string content_directory;
			std::string sabotaged_structure;
			std::string override_map_name;
			
			ia >> scenario_index;
			ia >> scenario_variation;
			ia >> scenario_direction;
			ia >> build_level;
			ia >> faction;
			ia >> game_type;
			ia >> content_directory;
			ia >> sabotaged_structure;
			ia >> override_map_name;
			CNC_Start_Instance_Variation(std::stoi(scenario_index), std::stoi(scenario_variation), std::stoi(scenario_direction), std::stoi(build_level), faction.c_str(), game_type.c_str(), content_directory.c_str(), std::stoi(sabotaged_structure), override_map_name.c_str());
			continue;
		}
		if (event_name == "CNC_Set_Home_Cell")
		{
			std::string x;
			std::string y;
			std::string player_id;
			ia >> x;
			ia >> y;
			ia >> player_id;
			CNC_Set_Home_Cell(std::stoi(x), std::stoi(y), std::stoll(player_id));
			continue;
		}
		if (event_name == "CNC_Set_Difficulty")
		{
			std::string difficulty;
			ia >> difficulty;
			CNC_Set_Difficulty(std::stoi(difficulty));
			continue;
		}	
		if (event_name == "CNC_Advance_Instance")
		{
			std::string player_id;
			ia >> player_id;
			if (!CNC_Advance_Instance(std::stoll(player_id)))
			{
				break;
			}
			continue;
		}
		if (event_name == "CNC_Handle_Input")
		{
			std::string mouse_event;
			std::string special_keys_flag;
			std::string player_id;
			std::string x1;
			std::string y1;
			std::string x2;
			std::string y2;
			ia >> mouse_event;
			ia >> special_keys_flag;
			ia >> player_id;
			ia >> x1;
			ia >> y1;
			ia >> x2;
			ia >> y2;
			CNC_Handle_Input((InputRequestEnum)std::stoi(mouse_event), std::stoi(special_keys_flag),0, std::stoi(x1), std::stoi(y1), std::stoi(x2), std::stoi(y2));
			continue;
		}
		if (event_name == "CNC_Handle_Sidebar_Request")
		{
			std::string request_type;
			std::string player_id;
			std::string buildable_type;
			std::string buildable_id;
			std::string cell_x;
			std::string cell_y;
			ia >> request_type;
			ia >> player_id;
			ia >> buildable_type;
			ia >> buildable_id;
			ia >> cell_x;
			ia >> cell_y;
			CNC_Handle_Sidebar_Request((SidebarRequestEnum)std::stoi(request_type), std::stoll(player_id),  std::stoi(buildable_type), std::stoi(buildable_id), std::stoi(cell_x), std::stoi(cell_y));
			continue;
		}
		if (event_name == "CNC_Get_Game_State")
		{
			std::string state_type;
			std::string player_id;
			std::string buffer_size;

			ia >> state_type;
			ia >> player_id;
			ia >> buffer_size;
			auto request_state = (GameStateRequestEnum)std::stoi(state_type);
			switch (request_state)
			{
				//case GameStateRequestEnum::GAME_STATE_STATIC_MAP:				{
				//	CNCMapDataStruct buffer_in = {};
				//	auto state = CNC_Get_Game_State(request_state, std::stoll(player_id), (unsigned char*)&buffer_in, std::stoi(buffer_size));
				//	break;				}
				//case GameStateRequestEnum::GAME_STATE_PLAYER_INFO:				{
				//	CNCPlayerInfoStruct buffer_in1 = {};
				//	auto state = CNC_Get_Game_State(request_state, std::stoll(player_id), (unsigned char*)&buffer_in1, std::stoi(buffer_size));
				//	break;				}
				//case GameStateRequestEnum::GAME_STATE_LAYERS:				{
				//	CNCObjectListStruct buffer_in2 = {};
				//	auto state = CNC_Get_Game_State(request_state, std::stoll(player_id), (unsigned char*)&buffer_in2, std::stoi(buffer_size));
				//	break;				}
				//case GameStateRequestEnum::GAME_STATE_OCCUPIER: {
				//	CNCOccupierHeaderStruct buffer_in3[100];// = {};
				//	auto state = CNC_Get_Game_State(request_state, std::stoll(player_id), (unsigned char*)&buffer_in3, std::stoi(buffer_size));
				//	break; }
				//case GameStateRequestEnum::GAME_STATE_PLACEMENT: {
				//	CNCPlacementInfoStruct  buffer_in4 = {};
				//	auto state = CNC_Get_Game_State(request_state, std::stoll(player_id), (unsigned char*)&buffer_in4, std::stoi(buffer_size));
				//	break; }
				//case GameStateRequestEnum::GAME_STATE_SHROUD: {
				//	CNCShroudStruct  buffer_in5 = {};
				//	auto state = CNC_Get_Game_State(request_state, std::stoll(player_id), (unsigned char*)&buffer_in5, std::stoi(buffer_size));
				//	break; }
				//case GameStateRequestEnum::GAME_STATE_SIDEBAR: {
				//	CNCSidebarStruct  buffer_in6 = {};
				//	auto state = CNC_Get_Game_State(request_state, std::stoll(player_id), (unsigned char*)&buffer_in6, std::stoi(buffer_size));
				//	break; }
				//case GameStateRequestEnum::GAME_STATE_DYNAMIC_MAP: {
				//	CNCDynamicMapStruct buffer_in7 = {};
				//	auto state = CNC_Get_Game_State(request_state, std::stoll(player_id), (unsigned char*)&buffer_in7, std::stoi(buffer_size));
				//	break; }
				default:
					break;
			}
			continue;
		}

    }

  
}

