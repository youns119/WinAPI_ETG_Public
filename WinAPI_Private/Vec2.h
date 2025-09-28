#pragma once

struct Vec2
{
public:
	Vec2()
		: fX(0.f)
		, fY(0.f)
	{}

	Vec2(const float _fX, const float _fY)
		: fX(_fX)
		, fY(_fY)
	{}

	Vec2(const int _iX, const int _iY)
		: fX((float)_iX)
		, fY((float)_iY)
	{}

	Vec2(const POINT& _tPoint)
		: fX((float)_tPoint.x)
		, fY((float)_tPoint.y)
	{}

public:
	Vec2& operator = (const POINT& _tPoint)
	{
		fX = (float)_tPoint.x;
		fY = (float)_tPoint.y;
	}

	bool operator == (const Vec2& _vInput)
	{
		if (fX == _vInput.fX && fY == _vInput.fY)
			return true;

		return false;
	}

	bool operator != (const Vec2& _vInput)
	{
		return !(*this == _vInput);
	}

	Vec2 operator + (const Vec2& _vInput)
	{
		return Vec2(fX + _vInput.fX, fY + _vInput.fY);
	}

	Vec2 operator + (const float _fValue)
	{
		return Vec2(fX + _fValue, fY + _fValue);
	}

	void operator += (const Vec2& _vInput)
	{
		fX += _vInput.fX;
		fY += _vInput.fY;
	}

	Vec2 operator - (const Vec2& _vInput)
	{
		return Vec2(fX - _vInput.fX, fY - _vInput.fY);
	}

	Vec2 operator - (const float _fValue)
	{
		return Vec2(fX - _fValue, fY - _fValue);
	}

	Vec2 operator - ()
	{
		return Vec2(-fX, -fY);
	}

	void operator -= (const Vec2& _vInput)
	{
		fX -= _vInput.fX;
		fY -= _vInput.fY;
	}

	Vec2 operator * (const Vec2& _vInput)
	{
		return Vec2(fX * _vInput.fX, fY * _vInput.fY);
	}

	Vec2 operator * (const int _iValue)
	{
		return Vec2(fX * float(_iValue), fY * float(_iValue));
	}

	Vec2 operator * (float _fValue)
	{
		return Vec2(fX * _fValue, fY * _fValue);
	}

	Vec2 operator *= (float _fValue)
	{
		fX *= _fValue;
		fY *= _fValue;
	}

	Vec2 operator / (const Vec2& _vInput)
	{
		assert(!(_vInput.fX == 0.f || _vInput.fY == 0.f));
		return Vec2(fX / _vInput.fX, fY / _vInput.fY);
	}

	Vec2 operator / (const float& _fValue)
	{
		assert(!(0.f == _fValue));
		return Vec2(fX / _fValue, fY / _fValue);
	}

public:
	bool IsZero()
	{
		if (fX == 0.f && fY == 0.f)
			return true;
			
		return false;
	}

	float Length()
	{
		return (float)sqrt(fX * fX + fY * fY);
	}

	Vec2 Normalize()
	{
		Vec2 vSelf(this->fX, this->fY);
		float fLength = this->Length();

		if (fLength == 0.f) fLength = .1f;

		//assert(fLength != 0.f);

		vSelf.fX /= fLength;
		vSelf.fY /= fLength;

		return vSelf;
	}

	float DirToRadian()
	{
		Vec2 vSelf(this->fX, this->fY);
		vSelf = this->Normalize();

		return atan2f(vSelf.fY, vSelf.fX);
	}

public:
	float fX;
	float fY;
};