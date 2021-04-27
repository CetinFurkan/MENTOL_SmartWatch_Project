void themeSpaceDrawWatch()
{
  drawSegmentWatchSmooth(color(210, 255, 255), c_green,   colorBack, colorBack, segWatchIsAlways || segWatchUpdated , true, false);

}

void themeSpace_init()
{
  setSegmentWatchMode(SEG_WATCH_ANIM_SMOOTH);
  setSegmentWatchMode(SEG_WATCH_SHOW_LINES);
  setSegmentWatchMode(SEG_WATCH_DRAW_ALWAYS);
  setSegmentWatchMode(SEG_WATCH_ENABLE);

  ssaverSetAnimation(SSAVER_STAR);
  ssaverSetParticleNumber(50);

  clearScreen(c_black);
}
