require 'date'

class Rank

  attr_reader :time

  def initialize(time)
    @time = time
  end

  def to_s
    @time.strftime("%Y-%m-%d %H:%M")
  end

  def hash
    @hash ||= to_s.hash
  end

  def eql?(other)
    self.hash == other.hash
  end

end

def parse_ltsv ltsv_string
  Hash[ltsv_string.split("\t").map{|f| f.split(":", 2)}]
end

{}.tap{ |ranks|
  ARGF.readlines.each{ |line|
    log = parse_ltsv(line)
    time = DateTime.strptime(log['time'], '%s').to_time
    rank = Rank.new(time)
    ranks[rank] ||= 0
    ranks[rank] += 1
  }
}.to_a.sort_by{ |rank|
  rank[0].time
}.each{ |number, rank|
  puts "#{rank.to_s}\t#{number}"
}
