#include <TFT_eSPI.h>
#include <string>

namespace qrcode {

class QRcode
{
	private:
        void render(int x, int y, int color, int borderOffset=0);
        int multiply{5};
        int m_tmpmult;

	public:
		void init();
        void create(std::string_view message);
        void setMultiply(int m);
        void createScaleToFit(std::string_view message, uint8_t border = 10);
};

} // namespace
