#include "../component.h"
#include "../../../networking/networking.h"

void comp_multiplayer_create(Component *comp)
{
    comp->alignment.x = ALIGN_CENTER;
    comp->alignment.y = ALIGN_CENTER;
    comp->a = 0.2;
    component_set_text(comp, 14, "MULTIPLAYER");
    comp->interactable = TRUE;
}

void comp_multiplayer_destroy(Component *comp)
{
    
}

void comp_multiplayer_update(Component *comp)
{

}

void comp_multiplayer_mouse_button_callback(Component *comp, i32 button, i32 action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        networking_init();
        component_destroy_children(comp_root);
        component_attach(comp_root, component_create(window.aspect_ratio / 2 - 0.2, 0.7, 0.4, 0.4 * 2.0/3, COMP_HOST, COLOR_TEX));
        component_attach(comp_root, component_create(window.aspect_ratio / 2 - 0.2, 0.3, 0.4, 0.4 * 2.0/3, COMP_JOIN, COLOR_TEX));
    }
}

void comp_multiplayer_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{

}

void comp_multiplayer_hover_callback(Component *comp, i32 action)
{
    
}