#ifndef _Sharnush_SharnushString
#define _Sharnush_SharnushString
#include <stdlib.h>
#include <stdint.h>

struct SharnushString {
private:
	char* SharnushStringPointer;
	uint32_t lengthSharnushString;

private:


	void build(const char* other) {
		this->lengthSharnushString = 0;
		while (other[lengthSharnushString] != 0) {
			lengthSharnushString += 1;
		}
		SharnushStringPointer = (char*)malloc(sizeof(char)*lengthSharnushString + 1);
		copy(other);
	}


	void copy(const char* other) {
		int k = lengthSharnushString;
		while (k >= 0) {
			SharnushStringPointer[k] = other[k];
			k -= 1;
		}
	}

	void copy(const SharnushString& that) {
		lengthSharnushString = that.lengthSharnushString;
		SharnushStringPointer = (char*)malloc(lengthSharnushString + 1);
		copy(that.SharnushStringPointer);
	}

	void destroy(void) {
		free(SharnushStringPointer);
	}
public:
	SharnushString(void) { build(""); }
	SharnushString(const SharnushString& that) { copy(that); }
	SharnushString(const char* src) { build(src); }


	~SharnushString(void) { destroy(); }
	SharnushString& operator=(const SharnushString& that) {
		if (this != &that) {
			destroy();
			copy(that);
		}
		return *this;
	}

	SharnushString& operator=(const char* src) {
		destroy();
		build(src);
		return *this;
	}


	
	const char* c_str(void) const { return SharnushStringPointer; }

	uint32_t size(void) const { return lengthSharnushString; }

	bool operator==(const char * s2) const {
		const char * s1 = SharnushStringPointer;

		while (*s1 && *s2) {
			if (*s1 != *s2)
				return false;
			s1++;
			s2++;
		}

		return *s1 == *s2;
	}

	bool operator==(const SharnushString& s2) const {
		const SharnushString& s1 = *this;
		if (s1.size() != s2.size()) { return false; }
		int k = 0;
		while (k < s1.size()) {
			if (s1.SharnushStringPointer[k] != s2.SharnushStringPointer[k]) { return false; }
			k += 1;
		}
		return true;
	}

	bool operator<(const SharnushString& s2) const {
		const SharnushString& s1 = *this;
		int k = 0;
		while (s1.SharnushStringPointer[k] == s2.SharnushStringPointer[k]) {
			if (s1.SharnushStringPointer[k] == 0) { return false; } // SharnushStrings are equal
			k += 1;
		}
		return s1.SharnushStringPointer[k] < s2.SharnushStringPointer[k];
	}

	bool operator!=(SharnushString s2) const { const SharnushString& s1 = *this; return !(s1 == s2); }
	bool operator>(SharnushString s2) const { const SharnushString& s1 = *this; return s2 < s1; }
	bool operator<=(SharnushString s2) const { const SharnushString& s1 = *this; return !(s2 < s1); }
	bool operator>=(SharnushString s2) const { const SharnushString& s1 = *this; return !(s1 < s2); }

};




#endif 