#ifndef Ch_D3D9_Fo_h
#define Ch_D3D9_Fo_h

namespace ChD3D9
{

	//標準機能で描画されるフォントクラス//
	class DrawFont:public ChCpp::ClassPerts::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		void Init(const LPDIRECT3DDEVICE9 _Dv);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		//描画する際のフォントサイズ//
		inline void SetFontSize(const unsigned long _W, const unsigned long _H) {
			FontW = _W;
			FontH = _H;
			Release();
			Init(Device);
		}

		///////////////////////////////////////////////////////////////////////////////////

		//フォントの描画//
		void Draw(
			std::string _DrawStr
			, const long _x
			, const long y
			, ChVec4 _Col = ChVec4(1.0f,1.0f,1.0f,1.0f));

		///////////////////////////////////////////////////////////////////////////////////

	protected:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		DrawFont() {}

		~DrawFont() { Release(); }


		LPD3DXFONT LpFont;
		LPDIRECT3DDEVICE9 Device;
		const long StartSize = 90;

		long FontW = StartSize;
		long FontH = StartSize;
		ChVec4 FontColor = { 1.0f,1.0f,1.0f,1.0f };
		std::string FontType;

	public:

		static DrawFont& GetIns()
		{
			static DrawFont Ins;
			return Ins;
		}
	};

	static const std::function<DrawFont&()>Font = DrawFont::GetIns;

}

#endif