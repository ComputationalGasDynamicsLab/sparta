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

ComputeStyle(react/isurf/grid,ComputeReactISurfGrid)

#else

#ifndef SPARTA_COMPUTE_REACT_ISURF_GRID_H
#define SPARTA_COMPUTE_REACT_ISURF_GRID_H

#include "compute.h"
#include "grid.h"
#include "surf.h"
#include "hash3.h"

namespace SPARTA_NS {

class ComputeReactISurfGrid : public Compute {
 public:
  ComputeReactISurfGrid(class SPARTA *, int, char **);
  ~ComputeReactISurfGrid();
  virtual void init();
  void compute_per_grid();
  virtual void clear();
  virtual void surf_tally(double, int, int, int, Particle::OnePart *,
                          Particle::OnePart *, Particle::OnePart *);
  virtual int tallyinfo(surfint *&);
  void post_process_isurf_grid();
  bigint memory_usage();

 protected:
  int groupbit;
  int isr;                 // index of surface reaction model
  int ntotal,rpflag;
  int maxgrid,combined;

  int **reaction2col;      // 1 if ireaction triggers tally for icol

  int ntally;              // # of surfs I have tallied for
  int maxtally;            // # of tallies currently allocated
  surfint *tally2surf;     // tally2surf[I] = surf ID of Ith tally

  // hash for surf IDs

#ifdef SPARTA_MAP
  typedef std::map<surfint,int> MyHash;
#elif defined SPARTA_UNORDERED_MAP
  typedef std::unordered_map<surfint,int> MyHash;
#else
  typedef std::tr1::unordered_map<surfint,int> MyHash;
#endif

  MyHash *hash;

  int dim;                 // local copies
  Surf::Line *lines;
  Surf::Tri *tris;

  void grow_tally();
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
