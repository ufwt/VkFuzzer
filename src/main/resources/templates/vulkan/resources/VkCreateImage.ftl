
    <#if config.isBad()>
    <#else>
    //ID: ${config.id}
    VkExtent3D ${config.extent} = {};
    ${config.extent}.width = ${config.width};
    ${config.extent}.height = ${config.height};
    ${config.extent}.depth = ${config.depth};

    VkImageCreateInfo ${config.vkImageCreateInfo} = {};
    ${config.vkImageCreateInfo}.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ${config.vkImageCreateInfo}.pNext = NULL;
    ${config.vkImageCreateInfo}.flags = ${config.flags?join(" | ")};
    ${config.vkImageCreateInfo}.imageType = ${config.imageType};
    ${config.vkImageCreateInfo}.format = ${config.format};
    ${config.vkImageCreateInfo}.extent = ${config.extent};
    ${config.vkImageCreateInfo}.mipLevels = ${config.mipLevels};
    ${config.vkImageCreateInfo}.arrayLayers = ${config.arrayLayers};
    ${config.vkImageCreateInfo}.samples = ${config.samples};
    ${config.vkImageCreateInfo}.tiling = ${config.tiling};
    ${config.vkImageCreateInfo}.usage = ${config.usage?join(" | ")};
    ${config.vkImageCreateInfo}.sharingMode = ${config.sharingMode};
    ${config.vkImageCreateInfo}.queueFamilyIndexCount = ${config.queueFamilyIndexCount};
    ${config.vkImageCreateInfo}.pQueueFamilyIndices = ${config.pQueueFamilyIndices};
    ${config.vkImageCreateInfo}.initialLayout = ${config.initialLayout};

    VkImage ${config.image};
    VkResult ${config.result} = vkCreateImage(${config.device}.device, &${config.vkImageCreateInfo},
            NULL, &${config.image});

    if (${config.result} != VK_SUCCESS)
    {
        std::cerr << "VkImage creation failed with wrong parameters" << std::endl;
        return EXIT_INVALID_CODE_GENERATION;
    }

    assert((${config.result} == VK_SUCCESS)
            || (${config.result} == VK_ERROR_OUT_OF_HOST_MEMORY)
            || (${config.result} == VK_ERROR_OUT_OF_DEVICE_MEMORY));

    if ((${config.result} == VK_ERROR_OUT_OF_HOST_MEMORY)
            || (${config.result} == VK_ERROR_OUT_OF_DEVICE_MEMORY))
    {
        std::cerr << "Run out of memory. Exiting gracefully." << std::endl;
        return EXIT_RUN_OUT_OF_MEMORY;
    }

    assert(${config.result} == VK_SUCCESS);
    </#if>
