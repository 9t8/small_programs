

#pragma once

#include <bits/stdc++.h>

class Graph {
public:
  void make_silly_snake() {
    _nodes = {{{1, "i-see"}},      {{2, "the-silly-snake"}}, {{3, "i-be"}},
              {{4, "you-saw-me"}}, {{5, "once-like"}},       {{0, "kekule"}}};
  }

  void make_mr_sticky() {
    _nodes = {{{1, "."}}, {{2, "."}, {3, "."}, {4, "."}}, {},
              {},         {{5, "."}, {6, "."}},           {},
              {}};
  }

  void make_driftin_dragonfly() {
    _nodes = {{{1, "dis-be-me-head"}},
              {{2, "me"}, {5, "dis-be-me"}, {9, "dis-be-me"}},
              {{3, "long-tail"}},
              {{4, "be-dis"}},
              {},
              {{6, "front-right"}},
              {{7, "me-right"}},
              {{8, "back"}},
              {{2, "be-dis"}},
              {{10, "front-left"}},
              {{11, "and-left"}},
              {{12, "back"}},
              {{2, "be-dis"}}};
  }

  void make_slinky_star() {
    _nodes = {{}};
    _nodes.resize(15);
    for (int i(1); i < 15; i += 2) {
      _nodes[0].push_back({i, "-"});
      _nodes[i] = {{i + 1, "-"}};
    }
  }

  void make_kathy_da_grate() {
    _nodes.clear();
    _nodes.resize(15);
    for (int i(0); i < 5; ++i) {
      _nodes[i] = {{(i + 1) % 5, "-"}, {2 * i + 5, "-"}};
      _nodes[2 * i + 5] = {{2 * i + 6, "-"}};
    }
  }

  void make_dodos_in_space() {
    _nodes.clear();
    _nodes.resize(50);
    for (int i(0); i < 50; i += 2)
      _nodes[i] = {{i + 1, "Yippee-Dodo-#" + std::to_string(i)}};
  }

  void make_purty_pitcher() {
    _nodes = {{{1, ""}}, {{2, ""}}, {{0, ""}}};
    sierpinski(2, 0);
  }

protected:
  friend class Tests;

  struct Edge {
    int _dst;
    std::string _tag;
  };

  std::vector<std::vector<Edge>> _nodes;

  void sierpinski(const int &depth, const int &i_v) {
    if (depth == 0)
      return;

    const int i_v1(_nodes[i_v].front()._dst), i_v2(_nodes[i_v1].front()._dst),
        i_midpts(_nodes.size());

    _nodes.push_back({{i_midpts + 2, ""}, {i_v1, ""}});
    _nodes.push_back({{i_midpts, ""}, {i_v2, ""}});
    _nodes.push_back({{i_midpts + 1, ""}, {i_v, ""}});

    _nodes[i_v].front() = {i_midpts, ""};
    _nodes[i_v1].front() = {i_midpts + 1, ""};
    _nodes[i_v2].front() = {i_midpts + 2, ""};

    sierpinski(depth - 1, i_v);
    sierpinski(depth - 1, i_v1);
    sierpinski(depth - 1, i_v2);
  }
};
