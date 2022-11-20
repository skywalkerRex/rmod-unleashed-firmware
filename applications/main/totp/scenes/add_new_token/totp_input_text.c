#include "totp_input_text.h"
#include <gui/view_i.h>
#include "../../types/common.h"

size_t strnlen(const char* s, size_t maxlen) {
    size_t len;

    for(len = 0; len < maxlen; len++, s++) {
        if(!*s) break;
    }

    return len;
}

static void commit_text_input_callback(void* context) {
    InputTextSceneState* text_input_state = (InputTextSceneState*)context;
    if(text_input_state->callback != 0) {
        InputTextSceneCallbackResult* result = malloc(sizeof(InputTextSceneCallbackResult));
        furi_check(result != NULL);
        result->user_input_length =
            strnlen(text_input_state->text_input_buffer, INPUT_BUFFER_SIZE);
        result->user_input = malloc(result->user_input_length + 1);
        furi_check(result->user_input != NULL);
        result->callback_data = text_input_state->callback_data;
        strlcpy(
            result->user_input,
            text_input_state->text_input_buffer,
            result->user_input_length + 1);
        text_input_state->callback(result);
    }
}

InputTextSceneState* totp_input_text_activate(InputTextSceneContext* context) {
    InputTextSceneState* text_input_state = malloc(sizeof(InputTextSceneState));
    furi_check(text_input_state != NULL);
    text_input_state->text_input = text_input_alloc();
    text_input_state->text_input_view = text_input_get_view(text_input_state->text_input);
    text_input_state->callback = context->callback;
    text_input_state->callback_data = context->callback_data;
    text_input_set_header_text(text_input_state->text_input, context->header_text);
    text_input_set_result_callback(
        text_input_state->text_input,
        commit_text_input_callback,
        text_input_state,
        &text_input_state->text_input_buffer[0],
        INPUT_BUFFER_SIZE,
        true);
    return text_input_state;
}

void totp_input_text_render(Canvas* const canvas, InputTextSceneState* text_input_state) {
    view_draw(text_input_state->text_input_view, canvas);
}

bool totp_input_text_handle_event(PluginEvent* const event, InputTextSceneState* text_input_state) {
    if(event->type == EventTypeKey) {
        view_input(text_input_state->text_input_view, &event->input);
    }

    return true;
}

void totp_input_text_free(InputTextSceneState* state) {
    text_input_free(state->text_input);
    free(state);
}
