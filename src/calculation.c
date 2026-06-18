#include "calculation.h"

double weighted_average(const int *votes, const int *credits, int n){
  int sum_votes = 0;
  int sum_credits = 0;
  for(int i = 0; i<n; i++){
    if(votes[i]>MAX_VOTE){
      sum_votes += 30*credits[i];
      sum_credits += credits[i];
    }else{
      sum_votes += votes[i]* credits[i];
      sum_credits += credits[i];
    }
  }
  if(sum_credits == 0) return 0.0;
  return (double)sum_votes/sum_credits;
}

double arithmetic_average(const int *votes, const int *credits, int n){
  int sum_votes = 0;
  for(int i = 0; i<n; i++){
    if(votes[i]>MAX_VOTE){
      sum_votes += 30;
    }else{
      sum_votes += votes[i];
    }
  }
  if(n == 0) return 0.0;
  return (double)sum_votes/n;
}

double institute_average(const int *votes, const int *credits, int n){
  int sum_votes = 0;
  int sum_credits = 0;
  for(int i = 0; i<n; i++){
    sum_votes += votes[i]* credits[i];
    sum_credits += credits[i];
  }
  if(sum_credits == 0) return 0.0;
  return (double)sum_votes/sum_credits;
}

double final_vote_average(double inst_average){
  return inst_average/30*110;
}


