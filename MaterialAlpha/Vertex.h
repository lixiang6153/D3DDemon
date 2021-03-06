#ifndef _VERTEX_H_
#define _VERTEX_H_

class CVertex
{
public:
	CVertex(){}
	CVertex(
		float x, float y, float z,
		float nx, float ny, float nz,
		float u, float v)
	{
		_x  = x;  _y  = y;  _z  = z;
		_nx = nx; _ny = ny; _nz = nz;
		_u  = u;  _v  = v;
	}
	float _x, _y, _z;
	float _nx, _ny, _nz;
	float _u, _v; // texture coordinates
};

#define FVF (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)	  // tex1����ʹ��tex0


#endif