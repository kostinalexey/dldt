// Copyright (C) 2018-2019 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include "mkldnn_async_infer_request.h"
#include <memory>

MKLDNNPlugin::MKLDNNAsyncInferRequest::MKLDNNAsyncInferRequest(const InferenceEngine::InferRequestInternal::Ptr &inferRequest,
                                                               const InferenceEngine::ITaskExecutor::Ptr &taskExecutor,
                                                               const InferenceEngine::TaskSynchronizer::Ptr &taskSynchronizer,
                                                               const InferenceEngine::ITaskExecutor::Ptr &callbackExecutor)
        : InferenceEngine::AsyncInferRequestThreadSafeDefault(inferRequest, taskExecutor, taskSynchronizer, callbackExecutor) {}

MKLDNNPlugin::MKLDNNAsyncInferRequest::~MKLDNNAsyncInferRequest() {
    waitAllAsyncTasks();
}

void MKLDNNPlugin::MKLDNNAsyncInferRequest::Infer() {
    std::cerr << __PRETTY_FUNCTION__ << "\n";

    _callbackManager.disableCallback();
    std::cerr << __PRETTY_FUNCTION__ << " 11\n";
    StartAsync();
    std::cerr << __PRETTY_FUNCTION__ << " 22\n";
    Wait(InferenceEngine::IInferRequest::WaitMode::RESULT_READY);
    std::cerr << __PRETTY_FUNCTION__ << " 33\n";
    _callbackManager.enableCallback();
    std::cerr << __PRETTY_FUNCTION__ << " 44\n";
}
