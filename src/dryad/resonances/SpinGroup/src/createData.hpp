static auto createData( std::vector< Channel > channels, ResonanceTable table ) {

  auto compare = [] ( auto&& left, auto&& right )
                    { return left.identifier() < right.identifier(); };
  std::sort( channels.begin(), channels.end(), compare );

  return std::make_tuple( std::move( channels ), std::move( table ) );
}

static auto createData( std::vector< ChannelData > channel_data ) {

  std::sort( channel_data.begin(), channel_data.end(),
             [] ( auto&& left, auto&& right )
                { return left.first.identifier() < right.first.identifier(); } );

  std::vector< Channel > channels( channel_data.size() );
  channels.reserve( channel_data.size() );
  std::transform( channel_data.begin(), channel_data.end(), channels.begin(),
                  [] ( auto&& channel ) { return std::move( channel.first ); } );

  ResonanceTable table = channel_data.front().second;
  for ( unsigned int i = 1; i < channel_data.size(); ++i ) {

    table += channel_data[i].second;
  }

  return std::make_tuple( std::move( channels ), std::move( table ) );
}