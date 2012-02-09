/*
    Copyright (c) 2002-2012 Tampere University of Technology.

    This file is part of TTA-Based Codesign Environment (TCE).

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
 */
/**
 * @file LLVMTCECmdLineOptions.hh
 *
 * Implementation of LLVMTCECmdLineOptions class.
 *
 * @author Veli-Pekka J��skel�inen 2008 (vjaaskel-no.spam-cs.tut.fi)
 * @author Pekka Jääskeläinen 2008-2012
 * @note rating: red
 */

#include "LLVMTCECmdLineOptions.hh"

const std::string LLVMTCECmdLineOptions::SWL_TARGET_MACHINE = "adf";
const std::string LLVMTCECmdLineOptions::SWS_TARGET_MACHINE = "a";
const std::string LLVMTCECmdLineOptions::SWL_OUTPUT_FILE = "output";
const std::string LLVMTCECmdLineOptions::SWS_OUTPUT_FILE = "o";
const std::string LLVMTCECmdLineOptions::SWL_SCHEDULER_CONFIG = "config";
const std::string LLVMTCECmdLineOptions::SWS_SCHEDULER_CONFIG = "c";
const std::string LLVMTCECmdLineOptions::SWL_EMULATION_LIB = "emulation";
const std::string LLVMTCECmdLineOptions::SWS_EMULATION_LIB = "e";
const std::string LLVMTCECmdLineOptions::SWL_DEBUG_FLAG = "debug";
const std::string LLVMTCECmdLineOptions::SWL_OPT_LEVEL = "optimize";
const std::string LLVMTCECmdLineOptions::SWS_OPT_LEVEL = "O";
const std::string LLVMTCECmdLineOptions::SWL_EXPERIMENTAL_REGALLOC = "experimental-ra";
const std::string LLVMTCECmdLineOptions::VERBOSE_SWITCH = "verbose";
const std::string LLVMTCECmdLineOptions::DISABLE_LLVMAA = "disable-llvmaa";
const std::string LLVMTCECmdLineOptions::CONSERVATIVE_PRE_RA_SCHEDULER= 
    "conservative-pre-ra-scheduler";

const std::string LLVMTCECmdLineOptions::SWL_DUMP_DDGS_DOT = "dump-ddgs-dot";
const std::string LLVMTCECmdLineOptions::SWL_DUMP_DDGS_XML = "dump-ddgs-xml";
const std::string LLVMTCECmdLineOptions::SWL_POM_BUILDER = "pom-builder";
const std::string LLVMTCECmdLineOptions::SWL_SAVE_BACKEND_PLUGIN = 
    "save-backend-plugin";
const std::string LLVMTCECmdLineOptions::SWL_BU_SCHEDULER = 
    "bottom-up-scheduler";
const std::string LLVMTCECmdLineOptions::SWL_RECURSIVE_BU_SCHEDULER = 
    "recursive-scheduler";
const std::string LLVMTCECmdLineOptions::SWL_USE_OLD_BACKEND_SOURCES = 
    "use-old-backend-src";

const std::string LLVMTCECmdLineOptions::SWL_TEMP_DIR = "temp-dir";

const std::string LLVMTCECmdLineOptions::ENABLE_VECTOR_BACKEND = 
    "vector-backend";

const std::string LLVMTCECmdLineOptions::USAGE =
    "Usage: llvmtce [OPTION]... BYTECODE\n"
    "Compile LLVM bytecode for target TCE architecture.\n";

/**
 * Constructor.
 */
LLVMTCECmdLineOptions::LLVMTCECmdLineOptions() {

    addOption(
        new StringCmdLineOptionParser(
            SWL_TARGET_MACHINE, "Target machine (.adf file)",
            SWS_TARGET_MACHINE));

    addOption(
        new StringCmdLineOptionParser(
            SWL_OUTPUT_FILE, "Output file name.",
            SWS_OUTPUT_FILE));

    addOption(
        new StringCmdLineOptionParser(
            SWL_SCHEDULER_CONFIG, "Scheduler configuration file.",
            SWS_SCHEDULER_CONFIG));

    addOption(
        new StringCmdLineOptionParser(
            SWL_EMULATION_LIB, "Emulation library bitcode file.",
            SWS_EMULATION_LIB));

    addOption(
        new IntegerCmdLineOptionParser(
            SWL_OPT_LEVEL, "Optimization level (0-2)",
            SWS_OPT_LEVEL));

    addOption(
        new BoolCmdLineOptionParser(
            SWL_EXPERIMENTAL_REGALLOC, "Use TCE's experimenal register allocator"));

    addOption(
        new BoolCmdLineOptionParser(
            SWL_DEBUG_FLAG, "Print LLVM debug data."));

    addOption(
        new BoolCmdLineOptionParser(
            VERBOSE_SWITCH, "The verbose switch", "v"));

    addOption(
        new BoolCmdLineOptionParser(
            DISABLE_LLVMAA, "Disable use of LLVM alias analysis.", 
            DISABLE_LLVMAA));

    addOption(
        new BoolCmdLineOptionParser(
            CONSERVATIVE_PRE_RA_SCHEDULER, 
            "Conservative pre-ra-scheduler. May decrease register usage but "
            "limit ILP. good for machines with low amount of registers."));

    addOption(
        new BoolCmdLineOptionParser(
            SWL_DUMP_DDGS_DOT, 
            "Dump DDGs in dot format before and after scheduling."));

    addOption(
        new BoolCmdLineOptionParser(
            SWL_DUMP_DDGS_XML, 
            "Dump DDGs in XML format before and after scheduling."));

    addOption(
        new BoolCmdLineOptionParser(
            SWL_POM_BUILDER, 
            "Use the old POM builder for converting LLVM MIs to POM."));

    addOption(
        new BoolCmdLineOptionParser(
            SWL_SAVE_BACKEND_PLUGIN,
            "Save the generated backend plugin for the architecture. "
            "This avoid the regeneration of the backend plugin when calling "
            "tcecc for the same architecture."));
    addOption(
        new BoolCmdLineOptionParser(
            SWL_BU_SCHEDULER, 
            "Use an experiment Bottom Up scheduler."));

    addOption(
        new BoolCmdLineOptionParser(
            SWL_RECURSIVE_BU_SCHEDULER, 
            "Use an experimental Bypassign Recursive Bottom Up scheduler."));

    addOption(
        new BoolCmdLineOptionParser(
            SWL_USE_OLD_BACKEND_SOURCES, 
            "Use the existing backend sources from the given temporary directory."));

    addOption(
        new StringCmdLineOptionParser(
            SWL_TEMP_DIR, 
            "The temporary directory to use for files needed during the code generation."));

    addOption(
	new BoolCmdLineOptionParser(
	    ENABLE_VECTOR_BACKEND,
	    "Enable backend support for vector registers split between multiple RF's"));
}

/**
 * Destructor.
 */
LLVMTCECmdLineOptions::~LLVMTCECmdLineOptions() {
}


/**
 * Returns path to the target .adf file defined with the -a switch.
 *
 * @return Target adf file defined in the command line.
 */
std::string
LLVMTCECmdLineOptions::machineFile() const {
    return findOption(SWS_TARGET_MACHINE)->String();
}

/**
 * Returns true if the target machine file is defined, false otherwise.
 *
 * @return True if the target machine file is defined.
 */
bool
LLVMTCECmdLineOptions::isMachineFileDefined() const {
    return findOption(SWS_TARGET_MACHINE)->isDefined();
}


/**
 * Returns scheduler configuration file defined with the -c switch.
 *
 * @return Scheduler configuration file defined in the command line.
 */
std::string
LLVMTCECmdLineOptions::schedulerConfigFile() const {
    return findOption(SWS_SCHEDULER_CONFIG)->String();
}

/**
 * Returns true if the scheduler config file is defined, false otherwise.
 *
 * @return True if the scheduler config file is defined.
 */
bool
LLVMTCECmdLineOptions::isSchedulerConfigFileDefined() const {
    return findOption(SWS_SCHEDULER_CONFIG)->isDefined();
}

std::string
LLVMTCECmdLineOptions::standardEmulationLib() const {
    return findOption(SWS_EMULATION_LIB)->String();
}

bool
LLVMTCECmdLineOptions::isStandardEmulationLibDefined() const {
    return findOption(SWS_EMULATION_LIB)->isDefined();
}

/**
 * Returns path to the output file defined with the -o switch.
 *
 * @return Output file name defined in the command line.
 */
std::string
LLVMTCECmdLineOptions::outputFile() const {
    return findOption(SWS_OUTPUT_FILE)->String();
}

/**
 * Returns true if the output file name is defined, false otherwise.
 *
 * @return True if the output file name is defined.
 */
bool
LLVMTCECmdLineOptions::isOutputFileDefined() const {
    return findOption(SWS_OUTPUT_FILE)->isDefined();
}

/**
 * Returns true if optimization level switch was given.
 *
 * @return True, if optimization level was given on command line.
 */
bool
LLVMTCECmdLineOptions::isOptLevelDefined() const {
    return findOption(SWS_OPT_LEVEL)->isDefined();
}


/**
 * Returns optimization level defined with the -O switch.
 *
 * @return Optimization level.
 */
int
LLVMTCECmdLineOptions::optLevel() const {
    return findOption(SWS_OPT_LEVEL)->integer();
}


/**
 * Returns true if the debug flag option was given.
 *
 * @return True, if debug mode switch was given.
 */
bool
LLVMTCECmdLineOptions::debugFlag() const {

    if (findOption(SWL_DEBUG_FLAG)->isDefined() &&
        findOption(SWL_DEBUG_FLAG)->isFlagOn()) {

        return true;
    }
    return false;
}

bool
LLVMTCECmdLineOptions::useExperimentalRegAllocator() const {
    return findOption(SWL_EXPERIMENTAL_REGALLOC)->isDefined();
}

bool
LLVMTCECmdLineOptions::disableLLVMAA() const {
    return findOption(DISABLE_LLVMAA)->isDefined();
}
/**
 * Return true if the verbose switch was defined in the command line.
 *
 * @return True if the verbose switch was defined in the command line.
 */
bool
LLVMTCECmdLineOptions::isVerboseSwitchDefined() const {
    return findOption(VERBOSE_SWITCH)->isDefined();
}

bool
LLVMTCECmdLineOptions::conservativePreRAScheduler() const {
    if (findOption(CONSERVATIVE_PRE_RA_SCHEDULER)->isDefined() &&
        findOption(CONSERVATIVE_PRE_RA_SCHEDULER)->isFlagOn()) {
        return true;
    }
    return false;
}

bool
LLVMTCECmdLineOptions::dumpDDGsDot() const {
    return findOption(SWL_DUMP_DDGS_DOT)->isDefined();
}

bool
LLVMTCECmdLineOptions::dumpDDGsXML() const {
    return findOption(SWL_DUMP_DDGS_XML)->isDefined();
}

bool
LLVMTCECmdLineOptions::usePOMBuilder() const {
    return findOption(SWL_POM_BUILDER)->isDefined();
}

bool
LLVMTCECmdLineOptions::saveBackendPlugin() const {
    return !(findOption(SWL_SAVE_BACKEND_PLUGIN)->isDefined() &&
             !findOption(SWL_SAVE_BACKEND_PLUGIN)->isFlagOn());
}
bool
LLVMTCECmdLineOptions::useBUScheduler() const {
    return findOption(SWL_BU_SCHEDULER)->isDefined();
}

bool
LLVMTCECmdLineOptions::useRecursiveBUScheduler() const {
    return findOption(SWL_RECURSIVE_BU_SCHEDULER)->isDefined();
}

bool
LLVMTCECmdLineOptions::useOldBackendSources() const {
    return findOption(SWL_USE_OLD_BACKEND_SOURCES)->isDefined();
}

TCEString
LLVMTCECmdLineOptions::tempDir() const {
    return findOption(SWL_TEMP_DIR)->String();
}

bool
LLVMTCECmdLineOptions::useVectorBackend() const {
    return findOption(ENABLE_VECTOR_BACKEND)->isDefined();
}
