template<typename Ok, typename Err>
class Result {
public:
  Result(Ok const & value);
  Result(Err const & value);

  Ok const & ok() const;
  Err const & err() const;

  bool is_ok() const;
  bool is_err() const;

private:
  struct ok_t { Ok value; };
  struct err_t { Err value; };
  std::variant<ok_t, err_t> _value;
};
