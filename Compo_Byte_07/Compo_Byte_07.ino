// Composite video and ByteBeat algo //

#include <M5Unified.h>
#include <M5UnitRCA.h>

#define WIDTH   256
#define HEIGHT  128

M5UnitRCA gfx_rca (WIDTH, HEIGHT, WIDTH, HEIGHT, M5UnitRCA::signal_type_t::PAL, M5UnitRCA::use_psram_t::psram_no_use, 26);

  long t, cnt, col;
  uint16_t coll;
  int16_t raw_data[WIDTH];

void setup(void) {

  M5.begin();
  M5.Display.clear(BLACK);
  M5.Display.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Display.drawString("ByteBeat video synthesizer", 5, 20);  

  auto spk_cfg        = M5.Speaker.config();
  spk_cfg.i2s_port    = I2S_NUM_1;
  spk_cfg.sample_rate = 48000;
  spk_cfg.pin_data_out = 15;
  spk_cfg.pin_bck      = 13;
  spk_cfg.pin_ws       = 0;  // LRCK
  spk_cfg.stereo        = true;
  spk_cfg.buzzer        = false;
  spk_cfg.use_dac       = false;
  spk_cfg.magnification = 16;
  M5.Speaker.config(spk_cfg);

  M5.Speaker.begin();
  M5.Speaker.setVolume(16);
  M5.Speaker.setChannelVolume(0, 255);
  M5.Speaker.setChannelVolume(1, 255);

  gfx_rca.init();
  gfx_rca.setOutputPin(26);

  gfx_rca.clear(TFT_BLACK);
    
}

void loop(void) {

for (int y = 0; y < HEIGHT; ++y) {

  for (int x = 0; x < WIDTH; ++x){

      col = t - (cnt&t^t-t>>2^t/256^t/t);

      gfx_rca.drawPixel((col+cnt)%WIDTH, y, coll);
      raw_data[x] = (int16_t)(cnt*col);

      t = t + 1;

    }

    M5.Speaker.playRaw(raw_data, WIDTH, 48000, false, 1, -1, false);

  }

  coll = col;
  cnt++;
 
}
