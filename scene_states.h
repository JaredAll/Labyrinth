#ifndef SCENE_STATES_H
#define SCENE_STATES_H

enum class Scene_States
{
  exit_right = 0,
  exit_left = 1,
  quit = 2,
  switch_tracks = 3
};

/* string states[] = */
/* { */
/*   "exit_right", */
/*   "exit_left", */
/*   "quit", */
/*   "switch_tracks" */
/* }; */

/* ostream& operator<<(ostream& out, const Scene_States state ) */
/* { */
/*   return out << states[ static_cast<int>(state) ]; */
/* } */

#endif
