// File: singleprop.h
// Author: Karl Moritz Hermann (mail@karlmoritz.com)
// Created: 03-01-2013
// Last Update: Mon 15 Sep 2014 13:39:53 BST
// Simple additive_avg model: Sum all vectors together and that's it.

#ifndef MODELS_ADDITIVE_AVG_SINGLEPROP_H
#define MODELS_ADDITIVE_AVG_SINGLEPROP_H

#include "../../common/shared_defs.h"
#include "../../common/singlepropbase.h"
#include "recursive_autoencoder.h"

namespace additive_avg {

class RecursiveAutoencoder;

class SingleProp : public SinglePropBase {
 public:
  SingleProp(RecursiveAutoencoderBase* rae, int sl, int nl, Real beta, Bools updates);
  /*virtual*/void loadWithSentence(const Corpus &t, int i);
  /*virtual*/void passDictLink(Real* data, int size);
  /*virtual*/void passDataLink(Real* data, int size);

  /*virtual*/void forwardPropagate(bool autoencode = false);
  /*virtual*/int backPropagate(bool lbl_error,
                               bool rae_error,
                               bool bi_error,
                               bool unf_error,
                               VectorReal *word = nullptr);
 private:
  // Various propagation functions.
  /*virtual*/void encodeInputs(int i, int child0, int child1, int rule, int rc0, int rc1, bool autoencode);
  /*virtual*/void encodeSingular(int i, int child0, int rule, int rc0, bool autoencode);
  /*virtual*/int applyLabel(int parent, bool updateWcat, Real beta);
  /*virtual*/void backpropInputs(int node, int child0, int child1, int rule, int rc0, int rc1, bool rae_error, bool unf_error);
  /*virtual*/void backpropWord(int node, int sent_pos);
  /*virtual*/void backpropBi(int node, VectorReal* word);

  // Variables.
  RecursiveAutoencoder* rae_;

  // Values (forward propagation).
  // WeightVectorsType  D_unnorm;

  // Inherited Gradients

  WeightMatrixType grad_D;
  WeightVectorType grad_Wl;
  WeightVectorType grad_Bl;
};

}  // namespace additive_avg
#endif  // MODELS_ADDITIVE_AVG_SINGLEPROP_H