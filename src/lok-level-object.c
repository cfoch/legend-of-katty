#include "lok.h"

LokLevelObject *
lok_level_object_new (tpointer data, LokLevelObjectType type)
{
  LokLevelObject *object;

  object = malloc (sizeof (LokLevelObject));
  if (type == LOK_LEVEL_OBJECT_TYPE_ELEMENT)
    object->data = data;
	else if (type == LOK_LEVEL_OBJECT_TYPE_ENEMY) {
		object->data = data;
		object->life_points = lok_enemy_get_life_points (LOK_ENEMY(data));
	}
  else
    object->data = NULL;
  object->type = type;
}

LokEnemy *
lok_level_object_get_enemy (LokLevelObject * object)
{
  LokEnemy *ret = NULL;
  if (object->type == LOK_LEVEL_OBJECT_TYPE_ENEMY)
    ret = LOK_ENEMY (object->data);
  return ret;
}

LokElement *
lok_level_object_get_element (LokLevelObject * object)
{
  LokElement *ret = NULL;
  if (object->type == LOK_LEVEL_OBJECT_TYPE_ELEMENT)
    ret = LOK_ELEMENT (object->data);
  return ret;
}

TBoolean
lok_level_object_is_enemy (LokLevelObject * object)
{
  return object->type == LOK_LEVEL_OBJECT_TYPE_ENEMY;
}

TBoolean
lok_level_object_is_element (LokLevelObject * object)
{
  return object->type == LOK_LEVEL_OBJECT_TYPE_ELEMENT;
}

void
lok_level_object_free (LokLevelObject * object)
{
  if (lok_level_object_is_element (object))
		lok_element_free (object->data);
	free (object);
}

TBoolean
lok_level_object_enemy_is_alive (LokLevelObject * object)
{
	return object->life_points > 0;
}
