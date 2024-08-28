#ifndef CONFIG_H_
#define CONFIG_H_

void core_config_set_game_path(char* p);
char* core_config_get_game_path();
char* core_config_get_asset_path(char* filename);
char* core_config_get_scripts_path(char* filename);

#endif // CONFIG_H_
