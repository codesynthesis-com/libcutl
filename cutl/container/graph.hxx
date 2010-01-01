// file      : cutl/container/graph.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2010 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CUTL_CONTAINER_GRAPH_HXX
#define CUTL_CONTAINER_GRAPH_HXX

#include <map>

#include <cutl/exception.hxx>
#include <cutl/shared-ptr.hxx>

namespace cutl
{
  namespace container
  {
    struct no_edge: exception {};

    template <typename N, typename E>
    class graph
    {
    public:
      typedef N node_base;
      typedef E edge_base;

    public:
      template <typename T>
      T&
      new_node ();

      template <typename T, typename A0>
      T&
      new_node (A0 const&);

      template <typename T, typename A0, typename A1>
      T&
      new_node (A0 const&, A1 const&);

      template <typename T, typename A0, typename A1, typename A2>
      T&
      new_node (A0 const&, A1 const&, A2 const&);

      template <typename T, typename A0, typename A1, typename A2,
                typename A3>
      T&
      new_node (A0 const&, A1 const&, A2 const&, A3 const&);

      template <typename T, typename A0, typename A1, typename A2,
                typename A3, typename A4>
      T&
      new_node (A0 const&, A1 const&, A2 const&, A3 const&, A4 const&);

      template <typename T, typename A0, typename A1, typename A2,
                typename A3, typename A4, typename A5>
      T&
      new_node (A0 const&, A1 const&, A2 const&, A3 const&, A4 const&,
                A5 const&);

      template <typename T, typename A0, typename A1, typename A2,
                typename A3, typename A4, typename A5, typename A6>
      T&
      new_node (A0 const&, A1 const&, A2 const&, A3 const&, A4 const&,
                A5 const&, A6 const&);

      template <typename T, typename A0, typename A1, typename A2,
                typename A3, typename A4, typename A5, typename A6,
                typename A7>
      T&
      new_node (A0 const&, A1 const&, A2 const&, A3 const&, A4 const&,
                A5 const&, A6 const&, A7 const&);

      template <typename T, typename A0, typename A1, typename A2,
                typename A3, typename A4, typename A5, typename A6,
                typename A7, typename A8>
      T&
      new_node (A0 const&, A1 const&, A2 const&, A3 const&, A4 const&,
                A5 const&, A6 const&, A7 const&, A8 const&);

      template <typename T, typename A0, typename A1, typename A2,
                typename A3, typename A4, typename A5, typename A6,
                typename A7, typename A8, typename A9>
      T&
      new_node (A0 const&, A1 const&, A2 const&, A3 const&, A4 const&,
                A5 const&, A6 const&, A7 const&, A8 const&, A9 const&);

      // template <typename T>
      // void
      // delete_node (T& node);

    public:
      template <typename T, typename L, typename R>
      T&
      new_edge (L&, R&);

      template <typename T, typename L, typename R,
                typename A0>
      T&
      new_edge (L&, R&, A0 const&);

      template <typename T, typename L, typename R,
                typename A0, typename A1>
      T&
      new_edge (L&, R&, A0 const&, A1 const&);

      template <typename T, typename L, typename R,
                typename A0, typename A1, typename A2>
      T&
      new_edge (L&, R&, A0 const&, A1 const&, A2 const&);

      template <typename T, typename L, typename R,
                typename A0, typename A1, typename A2, typename A3>
      T&
      new_edge (L&, R&, A0 const&, A1 const&, A2 const&, A3 const&);

      template <typename T, typename L, typename R,
                typename A0, typename A1, typename A2, typename A3,
                typename A4>
      T&
      new_edge (L&, R&, A0 const&, A1 const&, A2 const&, A3 const&,
                A4 const&);

      template <typename T, typename L, typename R,
                typename A0, typename A1, typename A2, typename A3,
                typename A4, typename A5>
      T&
      new_edge (L&, R&, A0 const&, A1 const&, A2 const&, A3 const&,
                A4 const&, A5 const&);

    public:
      template <typename T, typename L, typename R>
      void
      delete_edge (L&, R&, T& edge);

    public:
      graph () {}

    private:
      graph (graph const&);

      graph&
      operator= (graph const&);

    protected:
      typedef shared_ptr<node_base> node_ptr;
      typedef shared_ptr<edge_base> edge_ptr;

      typedef std::map<node_base*, node_ptr> nodes;
      typedef std::map<edge_base*, edge_ptr> edges;

      nodes nodes_;
      edges edges_;
    };
  }
}

#include <cutl/container/graph.txx>

#endif  // CUTL_CONTAINER_GRAPH_HXX
