//
// Created by Ilias Ahmindach on 23/12/2020.
//

#include "Subject.h"

const std::vector<std::shared_ptr<DungeonRunner::Observer>> &DungeonRunner::Subject::getSubjectObservers() const {
    return subjectObservers;
}
