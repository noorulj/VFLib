// Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
// See the file LICENSE.txt for licensing information.
// Based on ideas from the soci wrapper sqlite back-end.

#ifndef __VF_DB_STATEMENT_VFHEADER__
#define __VF_DB_STATEMENT_VFHEADER__

namespace db {

//
// Lightweight copyable handle to a statement. This
// is just a wrapper around the actual statement implementation.
//
class statement
{
public:
  statement (session& s);
  statement (detail::prepare_temp_type const& prep);
  ~statement ();

  statement (statement const& o);
  void operator= (statement const& o);

  void exchange (detail::into_type_ptr const& i);
  void exchange (detail::use_type_ptr const& u);

  void prepare (std::string const& query, bool bRepeatable=true);

  Error execute ();
  bool execute_and_fetch (Error& error);
  bool fetch (Error& error);

  bool got_data() const;
  rowid last_insert_rowid();

private:
  friend class detail::ref_counted_statement;

  void clean_up();

private:
  // STOP USING THIS!
  boost::shared_ptr <detail::statement_imp> m_imp;
};

}

#endif