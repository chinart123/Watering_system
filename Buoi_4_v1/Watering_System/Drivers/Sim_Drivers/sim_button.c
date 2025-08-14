#include "sim_button.h"
#include <stdlib.h>

int SimButton_GetState(int button_id) {
    return rand() % 2; // Trả về trạng thái ngẫu nhiên
}