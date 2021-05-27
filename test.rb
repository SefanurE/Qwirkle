#! /usr/bin/env ruby

# Test.rb - by Giraugh
# Run using "ruby test.rb" from your src dir or
# make it executable `chmod +x ./test.rb` and then execute it directly `./test.rb`

# You can pass a command to use for diffs as the first argument
# You can also pass -s to silence when no tests fail.
# I recommend using colordiff if you like colours.

require 'optparse'
require 'open3'

options = {}
OptionParser.new do |opts|
  opts.banner = "Usage: test.rb [-s/--silent] [difftool]"
  opts.on("-s", "--silent", "Run silently on success") do |v|
    options[:silent] = true
  end
  opts.on("-o", "--one", "Run only one test") do |v| options[:one] = true end
  opts.on("-c", "--no-clean", "Don't delete the .actual output") do |v| options[:noClean] = true end
end.parse!

silent = options[:silent]
diffCommand = ARGV[0] ? ARGV[0] : 'diff'
noClean = options[:noClean] or false

# Find tests
tests = Dir.glob('tests/standard/*.input')
if tests.length == 0 then
  puts "Found no tests. Will auto detect any .input files input this dir and subdirs." unless silent
  exit
end

if options[:one] then
tests = [tests[0]]
end

unless silent then
  puts "Running #{tests.length} tests..."
  puts ""
end
failedTests = []
tests.each { |t|
  name = t.match(/(.*)\.input$/)[1]

  # Run test
  _, stderr, status = Open3.capture3("./qwirkle < #{name}.input > #{name}.actual")

  unless status == 0 
    puts "  ❌ Failed to run test '#{name}'. Got status of '#{status}'"
    failedTests.push [name, "Running Test #{name} failed with error:\n\n#{stderr}"]
    next
  end

  # Do we have this file
  if not File.file?("#{name}.output") then
    puts "  🟡 Test '#{name}' is incomplete"
    next
  end

  # Perform a diff
  diff = `#{diffCommand} -u #{name}.output #{name}.actual`
  if diff != '' then
    puts "  ❌ Test '#{name}' failed!"
    failedTests.push [name, "Diff of failed test'#{name}'\n\n#{diff}"]
  else
    puts "  ✅ Test '#{name}' passed" unless silent
    File.delete("#{name}.actual") unless noClean
  end

  # clean up temp saves
  if File.exist?("#{name}.tmp.save") and not noClean then
    File.delete("#{name}.tmp.save")
  end
}

# Print stats
unless silent then
  puts ""
  puts "#{tests.length - failedTests.length} of #{tests.length} tests passed. "
  puts ""
end

# Print out failed tests
failedTests.each { |test|
  diff = test[1]
  if diff != '' then
    puts "-" * 60
    puts diff
    puts "\n" * 2
  end
}
