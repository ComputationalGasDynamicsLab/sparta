/* ----------------------------------------------------------------------
   SPARTA - Stochastic PArallel Rarefied-gas Time-accurate Analyzer
   http://sparta.sandia.gov
   Steve Plimpton, sjplimp@gmail.com, Michael Gallis, magalli@sandia.gov
   Sandia National Laboratories

   Copyright (2014) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level SPARTA directory.
------------------------------------------------------------------------- */

#ifdef COMPUTE_CLASS

ComputeStyle(collide/tally,ComputeCollideTally)

#else

#ifndef SPARTA_COMPUTE_COLLIDE_TALLY_H
#define SPARTA_COMPUTE_COLLIDE_TALLY_H

#include "compute.h"
#include "surf.h"

namespace SPARTA_NS {

class ComputeCollideTally : public Compute {
 public:
  ComputeCollideTally(class SPARTA *, int, char **);
  ~ComputeCollideTally();
  void init();
  void compute_per_tally();
  void clear();
  void surf_tally(int, int, int, Particle::OnePart *,
                          Particle::OnePart *, Particle::OnePart *);
  int tallyinfo(surfint *&);
  bigint memory_usage();

 protected:
  int groupbit,imix,nvalue;
  int *which;

  int ntally;              // # of surfs I have tallied for
  int maxtally;            // # of tallies currently allocated

  int dim;                 // local copies
  Surf::Line *lines;
  Surf::Tri *tris;

  virtual void grow_tally();
};

}

#endif
#endif

/* ERROR/WARNING messages:

E: Illegal ... command

Self-explanatory.  Check the input script syntax and compare to the
documentation for the command.  You can use -echo screen as a
command-line option when running SPARTA to see the offending line.

E: Compute surf mixture ID does not exist

Self-explanatory.

E: Number of groups in compute surf mixture has changed

This mixture property cannot be changed after this compute command is
issued.

*/
