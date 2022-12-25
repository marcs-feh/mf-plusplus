struct Nil {};

constexpr Nil NIL;

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

	Maybe(const Nil& nil_val){
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

template<class T>
bool operator==(const Maybe<T>& left, const T& right){
	if(left.is_nil){ return false; }
	return left.data == right;
}

template<class T>
bool operator==(const T& left, const Maybe<T>& right){
	if(right.is_nil){ return false; }
	return right.data == left;
}

template<class T>
bool operator==(const Maybe<T>& left, const Maybe<T>& right){
	if(left.is_nil || right.is_nil) {
		return left.is_nil && right.is_nil;
	}
	else {
		return left.data == right.data;
	}
}

template<class T>
bool operator!=(const Maybe<T>& left, const T& right){ return !(left == right); }

template<class T>
bool operator!=(const T& left, const Maybe<T>& right){ return !(left == right); }

template<class T>
bool operator!=(const Maybe<T>& left, const Maybe<T>& right){ return !(left == right); }

