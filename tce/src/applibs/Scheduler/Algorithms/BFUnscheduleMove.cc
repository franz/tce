/*
    Copyright (c) 2002-2014 Tampere University.

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
 * @file BFUnscheduleMove.cc
 *
 * Definition of BFUnscheduleMove class
 *
 * Unschedules a move.
 *
 * @author Heikki Kultala 2014-2020(heikki.kultala-no.spam-tuni.fi)
 * @note rating: red
 */

#include "BFUnscheduleMove.hh"
#include "Move.hh"
#include "DataDependenceGraph.hh"
#include "Bus.hh"
#include "POMDisassembler.hh"
#include "SimpleResourceManager.hh"
#include "Instruction.hh"
#include "MoveNodeDuplicator.hh"
#include "Terminal.hh"
#include "BF2Scheduler.hh"

void BFUnscheduleMove::unscheduleOriginal() {
    oldCycle_ = mn_.cycle();
    oldBus_ = &mn_.move().bus();

    if (mn_.isSourceOperation()) {
        srcFU_ = &mn_.move().source().functionUnit();
    }

    if (mn_.isDestinationOperation()) {
        dstFU_ = &mn_.move().destination().functionUnit();
    }

    if (mn_.move().source().isImmediateRegister()) {
        oldImmWriteCycle_ = rm().immediateWriteCycle(mn_);
        immRegIndex_ = mn_.move().source().index();
        immu_ = &mn_.move().source().immediateUnit();
    }

    MoveNode* prologMN = ii() ?  duplicator().getMoveNode(mn_) : NULL;
    if (prologMN != NULL) {
        prologBus_ = &prologMN->move().bus();

        if (prologMN->move().source().isImmediateRegister()) {
            prologImmWriteCycle_ = prologRM()->immediateWriteCycle(*prologMN);
        }

#ifdef DEBUG_BUBBLEFISH_SCHEDULER
        std::cerr << "\t\t\t\tProlog move: " << prologMN->toString() << std::endl;
        std::cerr << "\t\t\t\tBFUnscheduleMove Saving prolog bus: " << prologBus_->name() << " cycle: " << oldCycle_ << std::endl;
#endif
    }
#ifdef DEBUG_BUBBLEFISH_SCHEDULER
    for (int i = 0; i < recurseCounter_*2; i++)
        std::cerr << "\t";
        
    std::cerr << "\t\tUnscheduling original: " << mn_.toString() << " bus: " << oldBus_->name() << std::endl;
#endif
    unassign(mn_, false);
#ifdef DEBUG_BUBBLEFISH_SCHEDULER
    if (!canAssign(oldCycle_, mn_, oldBus_, srcFU_, dstFU_, prologBus_,
                   oldImmWriteCycle_, prologImmWriteCycle_)) {
        for (int i = 0; i < recurseCounter_*2; i++)
            std::cerr << "\t";

        std::cerr << "\t\tCannot assign to old cycle: " << mn_.toString()
                  << " old cycle: " << oldCycle_ << std::endl;
        ddg().writeToDotFile("cannot_assign_old_cycle.dot");
        if (mn_.isSourceOperation()) {
            std::cerr << "\t\twhole src PO: " << mn_.sourceOperation().toString()
                      << std::endl;
        }
        if (mn_.isDestinationOperation()) {
            std::cerr << "\t\twhole dst PO: " << mn_.destinationOperation().toString()
                      << std::endl;
        }
        assert(false);
    }
#endif
}

void BFUnscheduleMove::returnOriginal() {
#ifdef DEBUG_BUBBLEFISH_SCHEDULER
    for (int i = 0; i < recurseCounter_*2; i++)
        std::cerr << "\t";

    std::cerr << "\t\treturning original: " << mn_.toString() << " current bus: "
              << mn_.move().bus().name() << " old bus: " << oldBus_->name()
              << " cycle: " << oldCycle_ << std::endl;
#endif

#ifdef DEBUG_BUBBLEFISH_SCHEDULER
    if (!canAssign(oldCycle_, mn_, oldBus_, srcFU_, dstFU_, prologBus_,
                   oldImmWriteCycle_, prologImmWriteCycle_, immu_,
                   immRegIndex_, true)) {
        std::cerr << "Cannot return to old cycle: " << mn_.toString() << " cycle: " << oldCycle_  << std::endl;
        if (mn_.isDestinationOperation()) {
            std::cerr << "dstPO: " << mn_.destinationOperation().toString() << std::endl;
        }
        if (mn_.isSourceOperation()) {
            std::cerr << "srcPO: " << mn_.sourceOperation().toString() << std::endl;
        }
        std::cerr << "Original bus: " << oldBus_->name() << std::endl;
        ddg().writeToDotFile("cannot_return_old_cycle.dot");
        TTAProgram::Instruction* ins = rm().instruction(oldCycle_);
        for (int i = 0; i < ins->moveCount(); i++) {
            std::cerr << "\t" << POMDisassembler::disassemble(ins->move(i))
                      << " bus: " << ins->move(i).bus().name()
                      << std::endl;
        }
        std::cerr << "ins contains " << ins->immediateCount() << " immediates." << std::endl;
        assert(false);
    }
#endif
    assign(oldCycle_, mn_, oldBus_, srcFU_, dstFU_, prologBus_,
	   oldImmWriteCycle_, prologImmWriteCycle_, immu_, immRegIndex_);
}

void BFUnscheduleMove::undoOnlyMe() {
#ifdef DEBUG_BUBBLEFISH_SCHEDULER
    std::cerr << "BFUnscheudleMove undo" << std::endl;
#endif
    returnOriginal();
}

bool
BFUnscheduleMove::operator()() {
    unscheduleOriginal();
    return true;
}

int BFUnscheduleMove::recurseCounter_ = 0;
