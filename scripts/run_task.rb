#! /usr/bin/env ruby
#
require 'orocos'
require 'optparse'
require 'vizkit'

include Orocos
Orocos.initialize

Orocos.run 'dummy_component::Task' => 'dummy_component' do
    #Orocos.logger.level = Logger::DEBUG
    #Orocos.log_all
    dummy = Orocos::TaskContext.get 'dummy_component'
    dummy.io_port = "udp://127.0.0.1:1111:2222"
    begin
        dummy.configure
        dummy.start
    rescue
    end

    Vizkit.display dummy
    begin
        Vizkit.exec
    rescue Interrupt => e
        dummy.stop
    end
end

