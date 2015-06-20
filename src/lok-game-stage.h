#ifndef __LOK_GAME_STAGE__
#define __LOK_GAME_STAGE__

ClutterActor * lok_game_stage_pattern ();
ClutterLayoutManager * lok_game_stage_arena (LokGame * game);
void lok_game_stage_init (ClutterActor * stage, LokGame * game);

#endif /* __LOK_GAME_STAGE__ */
