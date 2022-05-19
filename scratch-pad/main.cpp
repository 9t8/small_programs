#include <bits/stdc++.h>

enum cat {
  ag,
  ca,
  cu,
  fe,
  sr,
  zn,
  pb,
  mn,
  al,
  ba,
  k,
  mg,
  na,
  nh4,
  sn,
  cr,
  co,
  ni,
  num_cats
};

enum an { no3, cl, i, po4, cro4, oh, br, co3, so4, c2o4, c2h3o2, num_ans };

using compound = std::pair<const cat, const an>;

struct mix {
  const compound s0, s1;
  const bool p;
};

using evidence_table =
    std::array<std::array<std::deque<int>, num_ans>, num_cats>;

std::ostream &operator<<(std::ostream &os, const evidence_table &t) {
  for (const auto &row : t) {
    for (const auto &cell : row) {
      os.width(4);
      os << cell.size();
    }
    os << '\n';
  }
  return os;
}

void table_to_list(const std::vector<compound> &rows,
                   const std::vector<compound> &cols,
                   const std::vector<std::vector<bool>> &table,
                   std::deque<mix> &list) {
  for (size_t row{}; row < rows.size(); ++row) {
    for (size_t col{}; col < cols.size(); ++col) {
      if (rows[row].first != cols[col].first &&
          rows[row].second != cols[col].second)
        list.push_back({rows[row], cols[col], table[row][col]});
    }
  }
}

void gen_mix_list(std::deque<mix> &mixes) {
  const std::vector<compound> s1_rows{
      {al, cl}, {ba, cl},  {k, i},     {k, po4},  {k, cro4},  {mg, cl},
      {na, oh}, {na, br},  {nh4, co3}, {na, so4}, {na, c2o4}, {na, c2h3o2},
      {sn, cl}, {cr, so4}, {co, cl},   {ni, cl}};

  const std::vector<compound> s1_cols{{ag, no3}, {ca, no3}, {cu, no3},
                                      {fe, no3}, {sr, no3}, {zn, no3},
                                      {pb, no3}, {mn, no3}};

  const std::vector<std::vector<bool>> s1_data{
      {1, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 1, 1},
      {1, 0, 1, 1, 0, 0, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1},
      {1, 0, 1, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 1},
      {1, 1, 1, 0, 1, 1, 1, 1}, {0, 0, 0, 0, 1, 0, 0, 0},
      {1, 1, 1, 0, 1, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
      {1, 0, 0, 1, 0, 0, 1, 1}, {1, 0, 0, 1, 0, 1, 1, 1},
  };

  const std::vector<compound> s2_rows{
      {na, so4}, {na, oh}, {na, br}, {na, c2o4}, {na, c2h3o2}};

  const std::vector<compound> s2_cols{{k, cro4}, {k, i}, {k, po4}, {nh4, co3}};

  const std::vector<std::vector<bool>> s2_data(5, std::vector(4, false));

  const std::vector<compound> s3_rows{{al, cl}, {ba, cl}, {mg, cl}, {sn, cl},
                                      {co, cl}, {ni, cl}, {cr, so4}};

  const std::vector<compound> s3_cols{{k, cro4},  {k, i},       {k, po4},
                                      {na, so4},  {na, oh},     {na, br},
                                      {na, c2o4}, {na, c2h3o2}, {nh4, co3}};

  const std::vector<std::vector<bool>> s3_data{
      {1, 0, 1, 0, 1, 0, 0, 0, 0}, {1, 0, 1, 1, 1, 0, 1, 0, 1},
      {0, 0, 1, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {1, 1, 1, 0, 1, 1, 1, 1, 1}, {0, 0, 1, 0, 1, 0, 0, 1, 1},
      {0, 0, 1, 0, 1, 1, 0, 0, 1}};

  mixes.clear();
  mixes.push_back({{}, {}, false}); // mixes are one-indexed
  table_to_list(s1_rows, s1_cols, s1_data, mixes);
  table_to_list(s2_rows, s2_cols, s2_data, mixes);
  table_to_list(s3_rows, s3_cols, s3_data, mixes);
}

void gen_sol_evi(const std::deque<mix> &mixes, evidence_table &sol_evi) {
  for (size_t i{1}; i < mixes.size(); ++i) {
    const mix &curr_mix{mixes[i]};
    if (!curr_mix.p) {
      sol_evi[curr_mix.s0.first][curr_mix.s0.second].push_back(i);
      sol_evi[curr_mix.s0.first][curr_mix.s1.second].push_back(i);
      sol_evi[curr_mix.s1.first][curr_mix.s0.second].push_back(i);
      sol_evi[curr_mix.s1.first][curr_mix.s1.second].push_back(i);
    }
  }
}

int main() {
  std::deque<mix> mixes;
  gen_mix_list(mixes);

  evidence_table sol_evi;
  gen_sol_evi(mixes, sol_evi);

  std::cout << sol_evi;

  std::cout << "DONE\n";
}
