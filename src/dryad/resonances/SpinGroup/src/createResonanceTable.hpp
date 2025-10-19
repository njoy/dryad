static ResonanceTable createResonanceTable( const std::vector< ChannelData >& channel_data ) {

  ResonanceTable table = channel_data.front().second;

  for ( unsigned int i = 1; i < channel_data.size(); ++i ) {

    table += channel_data[i].second;
  }

  return table;
}