
Data<BuildVersion::Build_1_1035_0_0, char, 0x1839EBDE1> mouse_acquired;

//// 
///*
//	force the game to use its own initialization of input rather than MCC
//	this function attempts to check if the GEHC is null and then proceeds to use
//	Member28
//*/
//HaloReach_2019_Jun_24_Hook<0x180780C20, __int64 __fastcall (c_profile_configuration* a1, int a2)> sub_180780C20 = [](c_profile_configuration* a1, int a2)
//{
//	set_player_name_and_tag();
//	auto callback = [=]() { return sub_180780C20(a1, a2); };
//	return IGameEngineHost::GEHCBypass<IGameEngineHost::GEHCBypassType::UseNullPointer>(callback);
//};

//intptr_t sub_18077D160_offset(EngineVersion engineVersion, BuildVersion buildVersion)
//{
//	switch (buildVersion)
//	{
//	case BuildVersion::Build_1_887_0_0: return 0x18077D160;
//	case BuildVersion::Build_1_1035_0_0: return 0x180495CC0;
//	}
//	return ~intptr_t();
//}
//
//FunctionHookEx<sub_18077D160_offset, __int16 __fastcall (__int64 a1, __int16* a2)> sub_18077D160 = [](__int64 a1, __int16* a2)
//{
//	auto callback = [=]() { return sub_18077D160(a1, a2); };
//	return IGameEngineHost::GEHCBypass<IGameEngineHost::GEHCBypassType::UseNullPointer>(g_game_engine_host_pointer, callback);
//};

void print_key_state_debug(s_bindings_table& bindingsTable)
{
	if (g_keyboardPrintKeyState)
	{
		for (int i = 0; i < _countof(bindingsTable.ControllerButtons); i++)
		{
			if (bindingsTable.ControllerButtons[i])
			{
				WriteLineVerbose("binding table %08lx was pressed value %08lx", i, bindingsTable.ControllerButtons[i]);
			}
		}
	}
}

intptr_t input_update_offset(EngineVersion engineVersion, BuildVersion buildVersion)
{
	switch (buildVersion)
	{
	case BuildVersion::Build_1_887_0_0: return 0x180307B10;
	case BuildVersion::Build_1_1035_0_0: return 0x18014C400;
	}
	return ~intptr_t();
}

#pragma optimize("", off)
FunctionHookEx<input_update_offset, char(__fastcall)()> input_update = []() 
{
	print_key_state_debug(g_input_abstraction.ptr()->BindingsTable[0]);

	char result = input_update();
	
	return result;
};
#pragma optimize("", on)

HaloReach_2019_Jun_24_Hook<0x180450C20, char(__stdcall)()> pan_cam_enabled = []()
{
	auto result = pan_cam_enabled();

	result = g_pancamEnabled;

	return result;
};

intptr_t input_abstraction_get_default_preferences_offset(EngineVersion engineVersion, BuildVersion buildVersion)
{
	switch (buildVersion)
	{
	case BuildVersion::Build_1_887_0_0: return 0x1803D8480;
	case BuildVersion::Build_1_1035_0_0: return 0x1801E80F0;
	}
	return ~intptr_t();
}
FunctionHookEx<input_abstraction_get_default_preferences_offset, __int64 __fastcall (s_bindings_table* a1)> input_abstraction_get_default_preferences = { "input_abstraction_get_default_preferences", [](s_bindings_table* a1)
{
	auto result = input_abstraction_get_default_preferences(a1);

	// 0 for left trigger
	// 1 for right trigger

	//memset(a1->ControllerButtons, 0, sizeof(a1->ControllerButtons));
	//for (int i = 0; i < _countof(a1->ControllerButtons); i++)
	//{
	//	a1->ControllerButtons[i] = e_controller_button_32::_controller_button_left_trigger;
	//}

	// default expected ordering
	assert(a1->ControllerButtons[_game_action_jump] == _controller_button_a);
	assert(a1->ControllerButtons[_game_action_switch_grenade] == _controller_button_b);
	assert(a1->ControllerButtons[_game_action_switch_weapon] == _controller_button_y);
	assert(a1->ControllerButtons[_game_action_context_primary] == _controller_button_x);
	assert(a1->ControllerButtons[_game_action_melee_attack] == _controller_button_right_bumper);
	assert(a1->ControllerButtons[_game_action_equipment] == _controller_button_left_bumper);
	assert(a1->ControllerButtons[_game_action_throw_grenade] == _controller_button_left_trigger);
	assert(a1->ControllerButtons[_game_action_fire_primary] == _controller_button_right_trigger);
	assert(a1->ControllerButtons[_game_action_crouch] == _controller_button_left_stick);
	assert(a1->ControllerButtons[_game_action_scope_zoom] == _controller_button_right_stick);
	assert(a1->ControllerButtons[_game_action_vehicle_brake] == _controller_button_left_trigger);
	assert(a1->ControllerButtons[_game_action_11] == _controller_button_b);
	assert(a1->ControllerButtons[_game_action_vehicle_brake2] == _controller_button_right_bumper);
	assert(a1->ControllerButtons[_game_action_13] == _controller_button_left_bumper);
	assert(a1->ControllerButtons[_game_action_14] == _controller_button_b);
	assert(a1->ControllerButtons[_game_action_15] == _controller_button_dpad_up);
	assert(a1->ControllerButtons[_game_action_16] == _controller_button_start);
	assert(a1->ControllerButtons[_game_action_show_weapon_details] == _controller_button_select);
	assert(a1->ControllerButtons[_game_action_18] == _controller_button_dpad_left);
	assert(a1->ControllerButtons[_game_action_19] == _controller_button_dpad_right);
	assert(a1->ControllerButtons[_game_action_night_vision] == _controller_button_dpad_left);
	assert(a1->ControllerButtons[_game_action_skip_cutscene] == _controller_button_a);
	assert(a1->ControllerButtons[_game_action_22] == _controller_button_b);
	assert(a1->ControllerButtons[_game_action_23] == _controller_button_dpad_down);
	assert(a1->ControllerButtons[_game_action_24] == _controller_button_dpad_up);
	assert(a1->ControllerButtons[_game_action_25] == _controller_button_dpad_left);
	assert(a1->ControllerButtons[_game_action_26] == _controller_button_dpad_right);
	assert(a1->ControllerButtons[_game_action_unknown_physics_debug1] == _controller_button_right_bumper);
	assert(a1->ControllerButtons[_game_action_unknown_physics_debug2] == _controller_button_left_bumper);
	assert(a1->ControllerButtons[_game_action_29] == _controller_button_dpad_up);
	assert(a1->ControllerButtons[_game_action_skip_cutscene_confirm] == _controller_button_y);
	assert(a1->ControllerButtons[_game_action_31] == _controller_button_dpad_up);
	assert(a1->ControllerButtons[_game_action_32] == _controller_button_dpad_down);
	assert(a1->ControllerButtons[_game_action_33] == _controller_button_select);
	assert(a1->ControllerButtons[_game_action_34] == _controller_button_dpad_left);
	assert(a1->ControllerButtons[_game_action_35] == _controller_button_x);
	assert(a1->ControllerButtons[_game_action_36] == _controller_button_select);
	assert(a1->ControllerButtons[_game_action_37] == _controller_button_dpad_up);
	assert(a1->ControllerButtons[_game_action_reload] == _controller_button_x);
	assert(a1->ControllerButtons[_game_action_39] == _controller_button_b);
	assert(a1->ControllerButtons[_game_action_40] == _controller_button_b);

	enum ControlsLayout
	{
		Default,
		SouthPaw,
		Boxer,
		GreenThumb,
		BumperJumper,
		Recon
	};

	switch (g_controlsLayout)
	{
	case SouthPaw:
		a1->ControllerButtons[_game_action_jump] = _controller_button_a;
		a1->ControllerButtons[_game_action_melee_attack] = _controller_button_right_bumper;
		a1->ControllerButtons[_game_action_switch_weapon] = _controller_button_y;
		a1->ControllerButtons[_game_action_switch_grenade] = _controller_button_b;
		a1->ControllerButtons[_game_action_equipment] = _controller_button_right_bumper;
		a1->ControllerButtons[_game_action_context_primary] = _controller_button_x;
		a1->ControllerButtons[_game_action_fire_primary] = _controller_button_right_trigger;
		a1->ControllerButtons[_game_action_throw_grenade] = _controller_button_left_trigger;
		a1->ControllerButtons[_game_action_scope_zoom] = _controller_button_right_stick;
		a1->ControllerButtons[_game_action_crouch] = _controller_button_left_stick;
		break;
	case Boxer:
		a1->ControllerButtons[_game_action_jump] = _controller_button_a;
		a1->ControllerButtons[_game_action_melee_attack] = _controller_button_left_trigger;
		a1->ControllerButtons[_game_action_switch_weapon] = _controller_button_y;
		a1->ControllerButtons[_game_action_switch_grenade] = _controller_button_b;
		a1->ControllerButtons[_game_action_equipment] = _controller_button_left_bumper;
		a1->ControllerButtons[_game_action_context_primary] = _controller_button_x;
		a1->ControllerButtons[_game_action_fire_primary] = _controller_button_right_trigger;
		a1->ControllerButtons[_game_action_throw_grenade] = _controller_button_right_bumper;
		a1->ControllerButtons[_game_action_scope_zoom] = _controller_button_right_stick;
		a1->ControllerButtons[_game_action_crouch] = _controller_button_left_stick;
		break;
	case GreenThumb:
		a1->ControllerButtons[_game_action_jump] = _controller_button_a;
		a1->ControllerButtons[_game_action_melee_attack] = _controller_button_right_stick;
		a1->ControllerButtons[_game_action_switch_weapon] = _controller_button_y;
		a1->ControllerButtons[_game_action_switch_grenade] = _controller_button_b;
		a1->ControllerButtons[_game_action_equipment] = _controller_button_left_bumper;
		a1->ControllerButtons[_game_action_context_primary] = _controller_button_x;
		a1->ControllerButtons[_game_action_fire_primary] = _controller_button_right_trigger;
		a1->ControllerButtons[_game_action_throw_grenade] = _controller_button_left_trigger;
		a1->ControllerButtons[_game_action_scope_zoom] = _controller_button_right_bumper;
		a1->ControllerButtons[_game_action_crouch] = _controller_button_left_stick;
		break;
	case BumperJumper:
		a1->ControllerButtons[_game_action_jump] = _controller_button_left_bumper;
		a1->ControllerButtons[_game_action_melee_attack] = _controller_button_right_bumper;
		a1->ControllerButtons[_game_action_switch_weapon] = _controller_button_y;
		a1->ControllerButtons[_game_action_switch_grenade] = _controller_button_a;
		a1->ControllerButtons[_game_action_equipment] = _controller_button_x;
		a1->ControllerButtons[_game_action_context_primary] = _controller_button_b;
		a1->ControllerButtons[_game_action_fire_primary] = _controller_button_right_trigger;
		a1->ControllerButtons[_game_action_throw_grenade] = _controller_button_left_trigger;
		a1->ControllerButtons[_game_action_scope_zoom] = _controller_button_right_stick;
		a1->ControllerButtons[_game_action_crouch] = _controller_button_left_stick;
		break;
	case Recon:
		a1->ControllerButtons[_game_action_jump] = _controller_button_a;
		a1->ControllerButtons[_game_action_melee_attack] = _controller_button_b;
		a1->ControllerButtons[_game_action_switch_weapon] = _controller_button_y;
		a1->ControllerButtons[_game_action_switch_grenade] = _controller_button_x;
		a1->ControllerButtons[_game_action_equipment] = _controller_button_left_bumper;
		a1->ControllerButtons[_game_action_context_primary] = _controller_button_right_bumper;
		a1->ControllerButtons[_game_action_fire_primary] = _controller_button_right_trigger;
		a1->ControllerButtons[_game_action_throw_grenade] = _controller_button_left_trigger;
		a1->ControllerButtons[_game_action_scope_zoom] = _controller_button_right_stick;
		a1->ControllerButtons[_game_action_crouch] = _controller_button_left_stick;
		break;
	default:
		break;
	}

	return result;
} };

intptr_t input_abstraction_get_default_keyboard_preferences_offset(EngineVersion engineVersion, BuildVersion buildVersion)
{
	switch (buildVersion)
	{
	case BuildVersion::Build_1_887_0_0: return 0x1803D8640;
	case BuildVersion::Build_1_1035_0_0: return 0x1801E82B0;
	}
	return ~intptr_t();
}
FunctionHookEx<input_abstraction_get_default_keyboard_preferences_offset, __int64 __fastcall (s_game_bindings& a1)> input_abstraction_get_default_keyboard_preferences = { "input_abstraction_get_default_keyboard_preferences", [](s_game_bindings& a1)
{
	auto result = input_abstraction_get_default_keyboard_preferences(a1);

	// mouse buttons
	a1.MouseBindings[_game_action_vehicle_brake].primary = e_mouse::_mouse_button3; // power slide
	a1.MouseBindings[_game_action_fire_primary].primary = e_mouse::_mouse_button1;
	a1.MouseBindings[_game_action_scope_zoom].primary = e_mouse::_mouse_button3;

	// mouse axis								
	a1.MouseAxisBindings[_game_action_mouse_axis_unknown45].primary = e_mouse_axis::_mouse_axis_unknown2;
	a1.MouseAxisBindings[_game_action_mouse_axis_unknown46].primary = e_mouse_axis::_mouse_axis_unknown3;
	a1.MouseAxisBindings[_game_action_mouse_axis_unknown47].primary = e_mouse_axis::_mouse_axis_unknown1;
	a1.MouseAxisBindings[_game_action_mouse_axis_unknown48].primary = e_mouse_axis::_mouse_axis_unknown0;

	// keyboard
	a1.KeyboardBindings[_game_action_jump].primary = _key_code_space;
	a1.KeyboardBindings[_game_action_switch_grenade].primary = _key_code_g;
	a1.KeyboardBindings[_game_action_switch_weapon].primary = _key_code_c;
	a1.KeyboardBindings[_game_action_context_primary].primary = _key_code_e;
	a1.KeyboardBindings[_game_action_melee_attack].primary = _key_code_q;
	a1.KeyboardBindings[_game_action_equipment].primary = _key_code_left_shift;
	a1.KeyboardBindings[_game_action_throw_grenade].primary = _key_code_f;
	a1.KeyboardBindings[_game_action_crouch].primary = _key_code_left_control;
	a1.KeyboardBindings[_game_action_vehicle_brake2].primary = _key_code_left_bracket; // vehicle trick
	a1.KeyboardBindings[_game_action_13].primary = _key_code_right_bracket;
	a1.KeyboardBindings[_game_action_16].primary = _key_code_escape;
	a1.KeyboardBindings[_game_action_show_weapon_details].primary = _key_code_back;
	a1.KeyboardBindings[_game_action_night_vision].primary = _key_code_m;
	a1.KeyboardBindings[_game_action_skip_cutscene].primary = _key_code_enter;
	a1.KeyboardBindings[_game_action_skip_cutscene_confirm].primary = _key_code_space;
	a1.KeyboardBindings[_game_action_35].primary = _key_code_space; // banshee flip?
	a1.KeyboardBindings[_game_action_36].primary = _key_code_tab;
	a1.KeyboardBindings[_game_action_37].primary = _key_code_z; // banshee bomb?
	a1.KeyboardBindings[_game_action_reload].primary = _key_code_r;
	a1.KeyboardBindings[_game_action_move_forward].primary = _key_code_w;
	a1.KeyboardBindings[_game_action_move_backwards].primary = _key_code_s;
	a1.KeyboardBindings[_game_action_move_left].primary = _key_code_a;
	a1.KeyboardBindings[_game_action_move_right].primary = _key_code_d;

	//a1.KeyboardBindings[_game_action_11].primary = _key_code_1;
	//a1.KeyboardBindings[_game_action_13].primary = _key_code_2;
	//a1.KeyboardBindings[_game_action_14].primary = _key_code_3;
	//a1.KeyboardBindings[_game_action_15].primary = _key_code_4;
	//a1.KeyboardBindings[_game_action_16].primary = _key_code_5;
	//a1.KeyboardBindings[_game_action_18].primary = _key_code_6;
	//a1.KeyboardBindings[_game_action_19].primary = _key_code_7;
	//a1.KeyboardBindings[_game_action_22].primary = _key_code_8;
	//a1.KeyboardBindings[_game_action_23].primary = _key_code_9;
	//a1.KeyboardBindings[_game_action_24].primary = _key_code_0;
	//a1.KeyboardBindings[_game_action_25].primary = _key_code_1;
	//a1.KeyboardBindings[_game_action_26].primary = _key_code_2;
	//a1.KeyboardBindings[_game_action_27].primary = _key_code_3;
	//a1.KeyboardBindings[_game_action_28].primary = _key_code_4;
	//a1.KeyboardBindings[_game_action_29].primary = _key_code_5;
	//a1.KeyboardBindings[_game_action_31].primary = _key_code_6;
	//a1.KeyboardBindings[_game_action_32].primary = _key_code_7;
	//a1.KeyboardBindings[_game_action_33].primary = _key_code_8;
	//a1.KeyboardBindings[_game_action_34].primary = _key_code_9;
	//a1.KeyboardBindings[_game_action_35].primary = _key_code_0;
	//a1.KeyboardBindings[_game_action_36].primary = _key_code_1;
	//a1.KeyboardBindings[_game_action_37].primary = _key_code_2; // switch nade
	//a1.KeyboardBindings[_game_action_39].primary = _key_code_3; // switch nade
	//a1.KeyboardBindings[_game_action_40].primary = _key_code_4;

	if (g_customBinds)
	{
		for (int i = 0; i < k_number_of_game_actions; i++)
		{
			DWORD primary = g_GameBindings.KeyboardBindings[i].primary;
			if (primary >= 0 && primary < k_number_of_key_codes)
			{
				a1.KeyboardBindings[i].primary = primary;
			}
		}
	}


	return result;
} };

// TODO: find a better home / move into own file
#pragma region Binds

struct Binds
{
	struct Bind
	{
		e_game_action GameAction;
		e_key_code KeyCode;

		Bind()
		{

		}

		Bind(e_game_action game_action, e_key_code key_code)
		{
			KeyCode = key_code;
			GameAction = game_action;
		}
		Bind(e_key_code key_code, e_game_action game_action)
		{
			KeyCode = key_code;
			GameAction = game_action;
		}

		template<int Count, typename T>
		T IndexOf(const char* Array[], const char* Input)
		{
			for (int i = 0; i < Count; i++)
			{
				if (strcmp(Array[i], Input) == 0)
					return (T)i;
			}

			return (T)0xFF;
		}

		e_key_code ReadFromConfig()
		{
			const char* pGameActionString = game_action_strings[GameAction];
			const char* pKeyCodeString = key_code_strings[KeyCode];
			char configResult[1024] = {};
			Settings::ReadStringValue(SettingsSection::Controls, pGameActionString, configResult, sizeof(configResult), pKeyCodeString);
			return IndexOf<k_number_of_key_codes, e_key_code>(key_code_strings, configResult);
		}
	};

	Bind bindingsBuffer[256];
	int Count = 0;

	void Reset()
	{
		ZeroMemory(&bindingsBuffer, sizeof(bindingsBuffer));
		Count = 0;
	}

	void Add(e_game_action game_action, e_key_code key_code)
	{
		assert(Count < _countof(bindingsBuffer));
		bindingsBuffer[Count++] = Bind(game_action, key_code);
	}

	void ReadBindsFromConfig(s_game_bindings& gameBindings)
	{
		memset(&gameBindings, 0xFF, sizeof(gameBindings));

		for (int i = 0; i < Count; i++)
		{
			gameBindings.KeyboardBindings[bindingsBuffer[i].GameAction].primary = bindingsBuffer[i].ReadFromConfig();
		}
	}
} g_Binds;

void ReadInputBindings()
{
	g_Binds.Reset();
	g_Binds.Add(_game_action_jump, _key_code_space);
	g_Binds.Add(_game_action_switch_grenade, _key_code_g);
	g_Binds.Add(_game_action_switch_weapon, _key_code_c);
	g_Binds.Add(_game_action_context_primary, _key_code_e);
	g_Binds.Add(_game_action_melee_attack, _key_code_q);
	g_Binds.Add(_game_action_equipment, _key_code_left_shift);
	g_Binds.Add(_game_action_throw_grenade, _key_code_f);
	g_Binds.Add(_game_action_crouch, _key_code_left_control);
	g_Binds.Add(_game_action_vehicle_brake2, _key_code_left_bracket);
	g_Binds.Add(_game_action_show_weapon_details, _key_code_back);
	g_Binds.Add(_game_action_night_vision, _key_code_4);
	g_Binds.Add(_game_action_skip_cutscene, _key_code_enter);
	g_Binds.Add(_game_action_skip_cutscene_confirm, _key_code_space);
	g_Binds.Add(_game_action_reload, _key_code_r);
	g_Binds.Add(_game_action_move_forward, _key_code_w);
	g_Binds.Add(_game_action_move_backwards, _key_code_s);
	g_Binds.Add(_game_action_move_left, _key_code_a);
	g_Binds.Add(_game_action_move_right, _key_code_d);

	if (g_customBinds = Settings::ReadBoolValue(SettingsSection::Controls, "CustomBinds", true))
		g_Binds.ReadBindsFromConfig(g_GameBindings);
}

#pragma endregion