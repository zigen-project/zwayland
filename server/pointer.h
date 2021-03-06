#ifndef ZWAYLAND_POINTER_H
#define ZWAYLAND_POINTER_H

#include <wayland-server.h>

#include "seat.h"
#include "surface.h"

struct zwl_pointer {
  struct wl_list link;
  struct wl_client *client;
  struct wl_list resource_list;
  struct wl_listener client_destroy_listener;

  struct {
    struct wl_resource *surface_resource;
    int32_t hotspot_x;
    int32_t hotspot_y;
  } pending_cursor;

  struct wl_listener pending_cursor_surface_commit_listener;
  struct wl_listener pending_cursor_surface_destroy_listener;
};

struct zwl_pointer *zwl_pointer_create(struct wl_client *client,
                                       struct zwl_seat *seat);

void zwl_pointer_destroy(struct zwl_pointer *pointer);

struct wl_resource *zwl_pointer_add_resource(struct zwl_pointer *pointer,
                                             struct wl_client *client,
                                             uint32_t id);

void zwl_pointer_send_enter(struct zwl_pointer *pointer,
                            struct zwl_surface *surface, wl_fixed_t x,
                            wl_fixed_t y);

void zwl_pointer_send_motion(struct zwl_pointer *pointer, uint32_t time,
                             wl_fixed_t x, wl_fixed_t y);

void zwl_pointer_send_leave(struct zwl_pointer *pointer,
                            struct zwl_surface *surface);

void zwl_pointer_send_button(struct zwl_pointer *pointer, uint32_t serial,
                             uint32_t time, uint32_t button, uint32_t state);

#endif  //  ZWAYLAND_POINTER_H
