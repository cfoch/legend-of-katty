#ifndef __LOK_H__
#define __LOK_H__

#define LOK_DEBUG_MSG                               "Debug"

#define LOK_MAX_LEVELS_NUMBER                       99
#define LOK_HERO_MAX_LIFE_POINTS                    1000
#define LOK_LEVEL_DEFAULT_LENGTH                    100
#define LOK_BELT_MAX_LENGTH                         8
#define LOK_BELT_POCKET_MAX_WEIGHT                  7
#define LOK_BELT_POCKET_MIN_WEIGHT                  1

#include <stdio.h>
#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <clutter-gtk/clutter-gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include "tlib.h"
#include "lok-types.h"
#include "lok-element.h"
#include "lok-bag-pack.h"
#include "lok-enemy.h"
#include "lok-level-object.h"
#include "lok-level.h"
#include "lok-belt.h"
#include "lok-game.h"
#include "lok-hero.h"

#include "lok-game-stage.h"

#include "lok-bag-pack-widget.h"
#include "lok-belt-widget.h"
#include "lok-heros-widget.h"
#include "lok-game-widget.h"

#endif /* __LOK_H__ */
