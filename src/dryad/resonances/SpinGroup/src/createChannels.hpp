static std::vector< Channel > createChannels( const std::vector< ChannelData >& channel_data ) {

  std::vector< Channel > channels;
  channels.reserve( channel_data.size() );

  for ( const auto& entry : channel_data ) {

    channels.emplace_back( entry.first );
  }

  return channels;
}