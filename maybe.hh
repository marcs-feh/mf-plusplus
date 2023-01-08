struct Nil_Type {};
constexpr Nil_Type Nil;

template<class T>
struct Maybe {
	T data;
	bool is_nil;

	Maybe(){
		is_nil = true;
	}

	Maybe(const T& data){
		this->data = data;
		is_nil = false;
	}

	Maybe(const Maybe<T>& opt){
		if(opt.is_nil){
			is_nil = true;
		} else {
			data = opt.data;
			is_nil = false;
		}
	}

	Maybe(const Nil_Type& nil_val){
		this->is_nil = true;
	}

	Maybe<T>& operator=(const T& data){
		this->data = data;
		this->is_nil  = false;
		return *this;
	}

	Maybe<T>& operator=(const Maybe<T>& opt){
		if(opt.is_nil){
			is_nil = true;
		}
		else {
			data = opt.data;
			is_nil = false;
		}
		return *this;
	}

};

// Comparison operators

// maybe == nil
template<class T>
bool operator==(const Maybe<T>& left, const Nil_Type& nil_val){
	return left.is_nil;
}

// nil == maybe
template<class T>
bool operator==(const Nil_Type& nil_val, const Maybe<T>& right){
	return right.is_nil;
}
// maybe == non-maybe
template<class T>
bool operator==(const Maybe<T>& left, const T& right){
	if(left.is_nil){ return false; }
	return left.data == right;
}

// non-maybe == maybe
template<class T>
bool operator==(const T& left, const Maybe<T>& right){
	if(right.is_nil){ return false; }
	return right.data == left;
}

// maybe == maybe
template<class T>
bool operator==(const Maybe<T>& left, const Maybe<T>& right){
	if(left.is_nil || right.is_nil) {
		return left.is_nil && right.is_nil;
	}
	else {
		return left.data == right.data;
	}
}

// maybe != nil
template<class T>
bool operator!=(const Maybe<T>& left, const Nil_Type& nil_val){ return !(left.is_nil); }

// nil != maybe
template<class T>
bool operator!=(const Nil_Type& nil_val, const Maybe<T>& right){ return !(right.is_nil); }

// maybe != non-maybe
template<class T>
bool operator!=(const Maybe<T>& left, const T& right){ return !(left == right); }

// non-maybe != maybe
template<class T>
bool operator!=(const T& left, const Maybe<T>& right){ return !(left == right); }

// maybe != maybe
template<class T>
bool operator!=(const Maybe<T>& left, const Maybe<T>& right){ return !(left == right); }

// Identity for nil
// nil == nil
static bool operator==(const Nil_Type&, const Nil_Type&){ return true; }

// nil != nil
static bool operator!=(const Nil_Type& left, const Nil_Type& right){ return !(left == right); }

