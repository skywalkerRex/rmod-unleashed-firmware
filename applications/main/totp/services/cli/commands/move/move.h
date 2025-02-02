#pragma once

#include <cli/cli.h>
#include "../../../../types/plugin_state.h"

#define TOTP_CLI_COMMAND_MOVE "move"
#define TOTP_CLI_COMMAND_MOVE_ALT "mv"

void totp_cli_command_move_handle(PluginState* plugin_state, FuriString* args, Cli* cli);
void totp_cli_command_move_docopt_commands();
void totp_cli_command_move_docopt_usage();
void totp_cli_command_move_docopt_options();