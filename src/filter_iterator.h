/*
 * Copyright 2018-2021 Redis Labs Ltd. and Contributors
 *
 * This file is available under the Redis Labs Source Available License Agreement
 */
#include "abstract_iterator.h"
#include "query_language.h"
#include "series_iterator.h"

#ifndef FILTER_ITERATOR_H
#define FILTER_ITERATOR_H

typedef struct SeriesFilterIterator
{
    AbstractIterator base;
    FilterByValueArgs byValueArgs;
    FilterByTSArgs ByTsArgs;
} SeriesFilterIterator;

SeriesFilterIterator *SeriesFilterIterator_New(AbstractIterator *input,
                                               FilterByValueArgs byValue,
                                               FilterByTSArgs ByTsArgs);

Chunk *SeriesFilterIterator_GetNextChunk(struct AbstractIterator *base);

void SeriesFilterIterator_Close(struct AbstractIterator *iterator);

typedef struct AggregationIterator
{
    AbstractIterator base;
    AggregationClass *aggregation;
    int64_t aggregationTimeDelta;
    timestamp_t timestampAlignment;
    void *aggregationContext;
    timestamp_t aggregationLastTimestamp;
    bool aggregationIsFirstSample;
    bool aggregationIsFinalized;
    bool reverse;
    bool initilized;
} AggregationIterator;

AggregationIterator *AggregationIterator_New(struct AbstractIterator *input,
                                             AggregationClass *aggregation,
                                             int64_t aggregationTimeDelta,
                                             timestamp_t timestampAlignment,
                                             bool reverse);
Chunk *AggregationIterator_GetNextChunk(struct AbstractIterator *iter);
void AggregationIterator_Close(struct AbstractIterator *iterator);

#endif // FILTER_ITERATOR_H
